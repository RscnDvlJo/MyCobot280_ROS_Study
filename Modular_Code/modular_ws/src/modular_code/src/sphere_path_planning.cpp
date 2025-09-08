/*
 * sphere_path_maker.cpp
 *
 *  Created on: August 4, 2025
 *      Author: Issac (RscnDvlJo)
 */


#include "modular_code/sphere_path_planning.h"


using namespace std;

SpherePathPlanning::SpherePathPlanning(double _radius, double _x, double _y, double _z, double _dist, PlannerConfig* _cfg): m_loader("robot/robot_description"){
	m_radius = _radius;
	
	m_x = _x;
	m_y = _y;
	m_z = _z;
	
	m_dist = _dist;
	
	m_pathsize = 0;
	
	m_cfg = _cfg;

}

SpherePathPlanning::~SpherePathPlanning(){


}


void SpherePathPlanning::genPathNPose(moveit_msgs::RobotTrajectory& out_traj, moveit_msgs::RobotState& out_start_state){
	int theta_size = 180/angular_resol;
	int phi_size = 90/angular_resol;
	
	m_pathsize = theta_size*phi_size;
	
	m_path.resize(m_pathsize, 3);
	m_robotQuaternion.resize(m_pathsize, 4);
	m_robotJointPath.resize(m_pathsize, 6);
	
	
	m_rotMat.resize(3,3);
	m_robotRotMat.resize(3,3);
	

	
	int cnt = 0;
	
	for (int i = 0; i < theta_size ; i++){
		for (int j = 0; j < phi_size; j++){
			double temp_theta_rad = 0.0;
			
			if(i < theta_size/2){
				temp_theta_rad = (90 + angular_resol*i)*PI/180;
			}else{
				temp_theta_rad = -(180 - angular_resol*(i-theta_size/2))*PI/180;
			}

			double temp_phi_rad = angular_resol*j*PI/180;
				
			calcTempRotMat(temp_theta_rad, temp_phi_rad);
			calcTempRobotRotMat(temp_theta_rad, temp_phi_rad);
			
			Eigen::Vector3d tempVec = m_rotMat*m_x_unit_vec;
			
			
			m_path(cnt, 0) = m_x + (m_radius + m_dist)*tempVec(0);	// x coord
			m_path(cnt, 1) = m_y + (m_radius + m_dist)*tempVec(1);	// y coord
			m_path(cnt, 2) = m_z + (m_radius + m_dist)*tempVec(2);	// z coord
			
			
			calcRobotQuaternion(m_robotRotMat, cnt);
			
			
			cnt++;
		}
	}

	std::vector<geometry_msgs::Pose> waypoints = makeWaypoints();

	setPlanningPrt(m_cfg);
	doPlanning(*m_cfg, waypoints, out_traj, out_start_state);
	

	// doInverseKinematics();
}



void SpherePathPlanning::calcTempRotMat(double _theta, double _phi){


m_rotMat << cos(_theta)*cos(_phi), 	-sin(_theta)*cos(_phi), 	sin(_phi),
	  sin(_theta), 		cos(_theta), 			0,
	  -cos(_theta)*sin(_phi), 	sin(_theta)*sin(_phi), 	cos(_phi);

}

void SpherePathPlanning::calcTempRobotRotMat(double _theta, double _phi){

m_robotRotMat << -cos(_theta)*cos(_phi), 	-sin(_theta)*cos(_phi), 	-sin(_phi),
	  	-sin(_theta), 			cos(_theta), 			0,
	  	cos(_theta)*sin(_phi), 	sin(_theta)*sin(_phi), 	-cos(_phi);
}

void SpherePathPlanning::calcRobotQuaternion(Eigen::Matrix3d _mat, int _i){

	// q = w + xi + yj + zk

	double w = 0.5 + sqrt(1+m_robotRotMat(0,0) + m_robotRotMat(1,1) + m_robotRotMat(2,2));	// w
	
	m_robotQuaternion(_i, 0) = w;
	m_robotQuaternion(_i, 1) = (m_robotRotMat(2,1) - m_robotRotMat(1,2))/(4+w);		// x
	m_robotQuaternion(_i, 2) = (m_robotRotMat(0,2) - m_robotRotMat(2,0))/(4+w);		// y
	m_robotQuaternion(_i, 3) = (m_robotRotMat(1,0) - m_robotRotMat(0,1))/(4+w);		// z

}

void SpherePathPlanning::doInverseKinematics(){

    m_robotJointPath.resize(m_pathsize, 6);

    // 1. Load robot model
    robot_model_loader::RobotModelLoader loader("robot/robot_description");
    robot_model::RobotModelPtr kmodel = loader.getModel();

    // 2. Create RobotState and JointModelGroup
    robot_state::RobotStatePtr kstate(new robot_state::RobotState(kmodel));
    kstate->setToDefaultValues();
    
    const robot_state::JointModelGroup* joint_model_group = 
        kmodel->getJointModelGroup("arm"); 

    const moveit::core::JointModelGroup* jmg = kmodel->getJointModelGroup("arm");
    

    if(!jmg->getSolverInstance()){
    	ROS_ERROR("No kinemtic solver");
    	return;
    
    }

    moveit::core::RobotState st(kmodel);
    st.setToDefaultValues();
    
    // std::vector<Eigen::VectorXd> path_mem;
    Eigen::VectorXd q_prev;
    bool have_seed = false;


    kinematics::KinematicsQueryOptions opt;
    opt.return_approximate_solution = true;
    const std::string tip = "joint6_flange";
    const std::string base = "g_base";

    
    // 3. Loop over all target poses
    for(int i = 0; i < (int)m_path.rows(); i++){
        if (have_seed) st.setJointGroupPositions(jmg, q_prev);
    
        geometry_msgs::Pose target_pose;
        
        // Position
        target_pose.position.x = m_path(i, 0);
        target_pose.position.y = m_path(i, 1);
        target_pose.position.z = m_path(i, 2);


        // Orientation
        target_pose.orientation.w = m_robotQuaternion(i, 0);
        target_pose.orientation.x = m_robotQuaternion(i, 1);
        target_pose.orientation.y = m_robotQuaternion(i, 2);
        target_pose.orientation.z = m_robotQuaternion(i, 3);

	
	bool ok = st.setFromIK(jmg, target_pose, tip, 0.3, moveit::core::GroupStateValidityCallbackFn(), opt);
	
	
	
	if(!ok){
		st.setToRandomPositions(jmg);
		ok = st.setFromIK(jmg, target_pose, tip, 0.3,  moveit::core::GroupStateValidityCallbackFn(), opt);
	
	}
	
	if(!ok){
		if (have_seed) 	m_robotJointPath.row(i) = q_prev.transpose();
		else 			m_robotJointPath.row(i).setConstant(std::numeric_limits<double>::quiet_NaN());
	}

        st.enforceBounds(jmg);
        st.copyJointGroupPositions(jmg, q_prev);
        have_seed = true;
        m_robotJointPath.row(i) = q_prev.transpose();

        
        
    }

}


void SpherePathPlanning::setPlanningPrt(PlannerConfig* _cfg){
	
	_cfg->group_name = "arm";
	_cfg->ee_link = "joint6_flange";
	_cfg->pos_tol = 1e-3;
	_cfg->rot_tol = 1e-2;
	_cfg->allowed_time = 2.0;


}

std::vector<geometry_msgs::Pose> SpherePathPlanning::makeWaypoints(){
	
	const int N = static_cast<int>(m_path.rows());
	if(m_robotQuaternion.rows() != N) throw std::runtime_error("path size error");
	
	std::vector<geometry_msgs::Pose> wps;
	wps.reserve(N);
	
	for (int i = 0; i < N; i++){
		
		geometry_msgs::Pose p;
		p.position.x = m_path(i,0);
		p.position.y = m_path(i,1);
		p.position.z = m_path(i,2);
	
	
		tf2::Quaternion q(m_robotQuaternion(i,0), m_robotQuaternion(i,1), m_robotQuaternion(i,2), m_robotQuaternion(i,3));
	
		// q.normalize();
		p.orientation = tf2::toMsg(q);
		
		wps.push_back(p);
	
	
	}
	
	
	return wps;

}

bool SpherePathPlanning::doPlanning(PlannerConfig _cfg, std::vector<geometry_msgs::Pose> _waypoints, moveit_msgs::RobotTrajectory& out_traj, moveit_msgs::RobotState& out_start_state){

    	m_model = m_loader.getModel();

	const auto* jmg = m_model->getJointModelGroup(_cfg.group_name);
	
	if (!jmg){
		ROS_ERROR_STREAM("Invaild group");
		return false;
	}
	
	robot_trajectory::RobotTrajectory accumulated(m_model, _cfg.group_name);
	
	moveit::core::RobotState cur = m_scene->getCurrentState();
	
	
	for (int i = 0; i < m_pathsize; i++){
	
		planning_interface::MotionPlanRequest req;
		planning_interface::MotionPlanResponse res;
		
		moveit::core::robotStateToRobotStateMsg(cur, req.start_state);
		req.group_name = _cfg.group_name;
		
		
		geometry_msgs::PoseStamped ps;
		ps.header.frame_id = "g_base";
		ps.pose = _waypoints[i];
	
		moveit_msgs::Constraints goal = kinematic_constraints::constructGoalConstraints(_cfg.ee_link, ps, _cfg.pos_tol, _cfg.rot_tol);
		
		req.goal_constraints = {goal};
		req.allowed_planning_time = _cfg.allowed_time;
		
		
		m_pipeline->generatePlan(m_scene, req, res);
		if(res.error_code_.val != moveit_msgs::MoveItErrorCodes::SUCCESS){
			ROS_WARN_STREAM("Planning fail");
			return false;
		}
		
		robot_trajectory::RobotTrajectoryPtr rt = res.trajectory_;
		
		if(!rt || rt->getWayPointCount() == 0){
			ROS_WARN("Empty trajectory");
			return false;
		}
		
		

		accumulated.append(*rt, rt->getWayPointDurationFromStart(rt->getWayPointCount()-1));
		
		
		cur = rt->getWayPoint(rt->getWayPointCount()-1);
		m_scene->setCurrentState(cur);
		
		
	}
	
	trajectory_processing::IterativeParabolicTimeParameterization iptp;
	bool ok = iptp.computeTimeStamps(accumulated, 1.0, 1.0);
	
	if(!ok){
		ROS_WARN("Time param filed");
	}
	

	accumulated.getRobotTrajectoryMsg(out_traj);
	moveit::core::robotStateToRobotStateMsg(m_scene->getCurrentState(), out_start_state);
	return true;
	

}

Eigen::MatrixXd* SpherePathPlanning::reqJointPath() {
	return &m_robotJointPath;
}

int SpherePathPlanning::reqPathSize() {
	return m_pathsize;
}
