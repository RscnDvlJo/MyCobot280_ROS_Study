/*
 * robot_description.cpp
 *
 *  Created on: September 19, 2025
 *      Author: Issac (RscnDvlJo)
 */
 
 #include "cobotrail/robot_description.h"

TrajectoryParams::TrajectoryParams(const std::string& group)
	: planning_group(group),
	move_group_interface(group),
	joint_model_group(nullptr)  
{
}

bool TrajectoryParams::initialize() {



	state = move_group_interface.getCurrentState();
	if (!state) {
		ROS_WARN("MoveGroupInterface current state is null! (joint_states not received yet)");
		return false;
	}

	joint_model_group = state->getJointModelGroup(planning_group);

	if (!joint_model_group) {
		ROS_ERROR("Joint model group %s not found!", planning_group.c_str());
		return false;
	}

	ROS_INFO("TrajectoryParams successfully initialized with group %s", planning_group.c_str());
	return true;

}


bool RobotDescription::initialize() {
	if (!m_robot_model) {
		ROS_ERROR("Robot model is NULL! URDF not loaded from /robot_description.");
		return false;
	}

	ROS_INFO("Robot model loaded: %zu joints, %zu variables",
	     m_robot_model->getJointModelCount(),
	     m_robot_model->getVariableCount());

	// TrajectoryParams도 초기화
	if (!m_trajectoryParams.initialize()) {
		ROS_ERROR("TrajectoryParams failed to initialize.");
		return false;
	}


	if (!m_trajectoryParams.joint_model_group) {
		ROS_ERROR("JointModelGroup '%s' not found in RobotModel!",
			  m_trajectoryParams.planning_group.c_str());
		return false;
	}

	ROS_INFO("JointModelGroup '%s' initialized with %zu joints",
	     m_trajectoryParams.planning_group.c_str(),
	     m_trajectoryParams.joint_model_group->getVariableCount());

	return true;
}




RobotDescription::RobotDescription()
	: m_trajectoryParams("arm"),
	  m_robot_model_loader("robot_description"),
	  m_robot_model(m_robot_model_loader.getModel())

      
	{
		m_joint_state.name = {
			"joint2_to_joint1",
			"joint3_to_joint2",
			"joint4_to_joint3",
			"joint5_to_joint4",
			"joint6_to_joint5",
			"joint6output_to_joint6",
			"linear_slide"
		};
		m_joint_state.position = std::vector<double>(7, 0.0);

		m_joint_traj.joint_names = m_joint_state.name;

	}






RobotDescription::~RobotDescription(){

}
 
sensor_msgs::JointState* RobotDescription::ret_joint_state(){
	return &m_joint_state;
}

trajectory_msgs::JointTrajectory* RobotDescription::ret_joint_traj() {
	return &m_joint_traj;
}

robot_state::RobotState* RobotDescription::ret_kinematic_state() {
	return m_trajectoryParams.state.get();
}

TrajectoryParams* RobotDescription::trajectoryParams(){
	return &m_trajectoryParams;
}
