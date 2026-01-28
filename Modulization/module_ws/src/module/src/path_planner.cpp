/*
 * path_planner.cpp
 *
 *  Created on: January 13, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 
#include "module/path_planner.h"

PathPlanner::PathPlanner(PathPlannerConfig& _pathConfig)
	: m_pathConfig(_pathConfig)
{
	m_radius = m_pathConfig.radius;
	m_dist = m_pathConfig.dist;
	m_center = m_pathConfig.center;

}

PathPlanner::~PathPlanner()
{
    
}

PathData PathPlanner::genPathNPose(){

	PathData _path;

	double _theta_resol = m_pathConfig.theta_move/m_pathConfig.num_angle_theta;
	double _phi_resol = m_pathConfig.phi_move/m_pathConfig.num_angle_phi;

	const size_t _pathsize = (m_pathConfig.num_angle_theta+1)*(m_pathConfig.num_angle_phi+1);


	_path.waypoints.reserve(_pathsize);


	for (int j = 0; j <= m_pathConfig.num_angle_theta; ++j) {
		double _theta_rad = (_theta_resol * j + m_pathConfig.theta_shift) * M_PI/180.0;

		if (j % 2 == 0) {
			// even layer: phi + dir
			for (int i = 0; i <= m_pathConfig.num_angle_phi; ++i) {
				double _phi_rad = (_phi_resol * i + m_pathConfig.phi_shift) * M_PI/180.0;

				calcTempRotMat(_phi_rad, _theta_rad);    // R = Rz(phi) * Ry(theta)
				calcTempRobotRotMat();                 // R_robot = R * Ry(pi) 

				Eigen::Vector3d _rhat = m_rotMat * m_unit_vec;
				Eigen::Vector3d _pos =
				m_center + (m_radius + m_dist) * _rhat;

				Eigen::Quaterniond _q = calcRobotQuaternion();

				geometry_msgs::Pose _pose;
				_pose.position.x = _pos.x();
				_pose.position.y = _pos.y();
				_pose.position.z = _pos.z();
				_pose.orientation.x = _q.x();
				_pose.orientation.y = _q.y();
				_pose.orientation.z = _q.z();
				_pose.orientation.w = _q.w();

				_path.waypoints.push_back(_pose);

			}


		} 

		else {
			// odd layer: phi - dir
			for (int i = m_pathConfig.num_angle_phi; i >= 0; --i) {
				double _phi_rad = (_phi_resol * i + m_pathConfig.phi_shift) * M_PI/180.0;

				calcTempRotMat(_phi_rad, _theta_rad);    // R = Rz(phi) * Ry(theta)
				calcTempRobotRotMat();                 // R_robot = R * Ry(pi) 

				Eigen::Vector3d _rhat = m_rotMat * m_unit_vec;
				Eigen::Vector3d _pos =
				m_center + (m_radius + m_dist) * _rhat;

				Eigen::Quaterniond _q = calcRobotQuaternion();

				geometry_msgs::Pose _pose;
				_pose.position.x = _pos.x();
				_pose.position.y = _pos.y();
				_pose.position.z = _pos.z();
				_pose.orientation.x = _q.x();
				_pose.orientation.y = _q.y();
				_pose.orientation.z = _q.z();
				_pose.orientation.w = _q.w();

				_path.waypoints.push_back(_pose);
			}
		}
	}

	return _path;

}





void PathPlanner::calcTempRotMat(double phi, double theta){
	// Rotation about Z (phi)
	m_rotMat_phi <<
	std::cos(phi), -std::sin(phi), 0,
	std::sin(phi),  std::cos(phi), 0,
	0,              0,             1;

	// Rotation about Y (theta)
	m_rotMat_theta <<
	 std::cos(theta), 0, std::sin(theta),
	 0,               1, 0,
	-std::sin(theta), 0, std::cos(theta);

	// Combined rotation
	m_rotMat = m_rotMat_phi * m_rotMat_theta;


	/*
	Eigen::Vector3d rhat_by_formula( sin(_theta)*cos(_phi),
		               sin(_theta)*sin(_phi),
		               cos(_theta) );
	ROS_INFO_STREAM("col3=" << m_rotMat.col(2).transpose()
	      << "  rhat_formula=" << rhat_by_formula.transpose());



	ROS_INFO_STREAM("calcTempRotMat: theta=" << _theta << ", phi=" << _phi);
	ROS_INFO_STREAM("m_rotMat = \n" << m_rotMat);
	*/


}



void PathPlanner::calcTempRobotRotMat(){
	// Rotation of pi about Y-axis
	m_rotMat_spin <<
	-1, 0,  0,
	 0, 1,  0,
	 0, 0, -1;

	m_robotRotMat = m_rotMat * m_rotMat_spin;
}

Eigen::Quaterniond PathPlanner::calcRobotQuaternion() const
{
	Eigen::Quaterniond q(m_robotRotMat);
	q.normalize();   // 항상 정규화 (안전)
	return q;

	/*
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
	*/

}

