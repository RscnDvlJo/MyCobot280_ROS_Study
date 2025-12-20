/*
 * sphere_path_maker.cpp
 *
 *  Created on: August 4, 2025
 *      Author: Issac (RscnDvlJo)
 */


#include "cobotrail/sphere_path_planning.h"


using namespace std;

SpherePathPlanning::SpherePathPlanning(double _radius, double _x, double _y, double _z, double _dist, PlannerConfig* _cfg): m_loader("robot_description"){
	m_radius = _radius;
	
	m_x = _x;
	m_y = _y;
	m_z = _z;
	
	m_dist = _dist;
	
	m_pathsize = 0;
	
	m_cfg = _cfg;
	
	m_unit_vec = Eigen::Vector3d(0.0, 0.0, 1.0);

}

SpherePathPlanning::~SpherePathPlanning(){


}


void SpherePathPlanning::genPathNPose(){

	
	double theta_resol = theta_move/num_angle_theta;
	double phi_resol = phi_move/num_angle_phi;
	
	m_pathsize = (num_angle_theta+1)*(num_angle_phi+1);
	
	
	
	
	m_path.resize(m_pathsize, 3);
	m_robotQuaternion.resize(m_pathsize, 4);
	m_robotJointPath.resize(m_pathsize, 6);
	
	
	m_rotMat.resize(3,3);
	m_robotRotMat.resize(3,3);
	
	m_rotMat_spin.resize(3,3);
	
	m_rotMat_phi.resize(3,3);
	m_rotMat_theta.resize(3,3);



	
	int cnt = 0;
	
	for (int j = 0; j <= num_angle_theta; ++j) {
		double theta_rad = (theta_move/num_angle_theta * j + theta_shift) * M_PI/180.0;

		if (j % 2 == 0) {
			// even layer: phi + dir
			for (int i = 0; i <= num_angle_phi; ++i) {
				double phi_rad = (phi_move/num_angle_phi * i + phi_shift) * M_PI/180.0;

				calcTempRotMat(phi_rad, theta_rad);    // R = Rz(phi) * Ry(theta)
				calcTempRobotRotMat();                 // R_robot = R * Ry(pi) 

				Eigen::Vector3d rhat = m_rotMat * m_unit_vec;
				m_path(cnt,0) = m_x + (m_radius + m_dist) * rhat.x();
				m_path(cnt,1) = m_y + (m_radius + m_dist) * rhat.y();
				m_path(cnt,2) = m_z + (m_radius + m_dist) * rhat.z();

				calcRobotQuaternion(m_robotRotMat, cnt);

			// z_axis ≈ -rhat, det ≈ +1
			++cnt;
			}
		
		
		} 
		
		else {
			// odd layer: phi - dir
			for (int i = num_angle_phi; i >= 0; --i) {
				double phi_rad = (phi_move/num_angle_phi * i + phi_shift) * M_PI/180.0;

				calcTempRotMat(phi_rad, theta_rad);    // R = Rz(phi) * Ry(theta)
				calcTempRobotRotMat();                 // R_robot = R * Ry(pi) 

				Eigen::Vector3d rhat = m_rotMat * m_unit_vec;
				m_path(cnt,0) = m_x + (m_radius + m_dist) * rhat.x();
				m_path(cnt,1) = m_y + (m_radius + m_dist) * rhat.y();
				m_path(cnt,2) = m_z + (m_radius + m_dist) * rhat.z();

				calcRobotQuaternion(m_robotRotMat, cnt);


			// z_axis ≈ -rhat, det ≈ +1

			++cnt;
			}
		}
	}

}



void SpherePathPlanning::calcTempRotMat(double _phi, double _theta){

	
	m_rotMat_phi		<<	std::cos(_phi),	-std::sin(_phi),	0,
					std::sin(_phi),	std::cos(_phi),	0,
					0,			0,		1;
					
	m_rotMat_theta		<<	std::cos(_theta),	0,		std::sin(_theta),
					0,			1,		0,
					-std::sin(_theta),	0,		std::cos(_theta);
	
	
	m_rotMat = m_rotMat_phi*m_rotMat_theta;
	  
	Eigen::Vector3d rhat_by_formula( sin(_theta)*cos(_phi),
		                         sin(_theta)*sin(_phi),
		                         cos(_theta) );
	ROS_INFO_STREAM("col3=" << m_rotMat.col(2).transpose()
		        << "  rhat_formula=" << rhat_by_formula.transpose());

	  
	  
	ROS_INFO_STREAM("calcTempRotMat: theta=" << _theta << ", phi=" << _phi);
	ROS_INFO_STREAM("m_rotMat = \n" << m_rotMat);
	  
}


void SpherePathPlanning::calcTempRobotRotMat(){
	

	
	m_rotMat_spin << 	-1,  0,  0,
			 	0,  1,  0,
				0,  0,  -1;	
	
	  	
	m_robotRotMat = m_rotMat*m_rotMat_spin;
}



void SpherePathPlanning::calcRobotQuaternion(Eigen::Matrix3d _mat, int _i)
{
    Eigen::Quaterniond q(_mat);  // Eigen이 내부적으로 동일 계산 수행
    q.normalize();

    // --- Hemisphere Fix: 이전 quaternion과 같은 반구 유지 ---
    if (_i > 0) {
        Eigen::Quaterniond q_prev(
            m_robotQuaternion(_i-1,0),    // w
            m_robotQuaternion(_i-1,1),    // x
            m_robotQuaternion(_i-1,2),    // y
            m_robotQuaternion(_i-1,3)     // z
        );

        // dot < 0 이면 서로 반대 hemisphere → 뒤집어 부호 반전
        if (q_prev.dot(q) < 0.0) {
            q.coeffs() *= -1.0;
        }
    }

    m_robotQuaternion(_i,0) = q.w();
    m_robotQuaternion(_i,1) = q.x();
    m_robotQuaternion(_i,2) = q.y();
    m_robotQuaternion(_i,3) = q.z();
}



std::vector<geometry_msgs::Pose> SpherePathPlanning::makeWaypoints() {
	std::vector<geometry_msgs::Pose> waypoints;
	waypoints.reserve(m_pathsize);

	for (int i = 0; i < m_pathsize; i++) {
		geometry_msgs::Pose pose;
		pose.position.x = m_path(i, 0);
		pose.position.y = m_path(i, 1);
		pose.position.z = m_path(i, 2);

		pose.orientation.w = m_robotQuaternion(i, 0);
		pose.orientation.x = m_robotQuaternion(i, 1);
		pose.orientation.y = m_robotQuaternion(i, 2);
		pose.orientation.z = m_robotQuaternion(i, 3);

		waypoints.push_back(pose);
	}
	return waypoints;
}
 
