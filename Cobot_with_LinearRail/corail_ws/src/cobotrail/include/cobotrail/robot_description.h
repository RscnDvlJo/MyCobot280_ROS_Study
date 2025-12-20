/*
 * robot_description.h
 *
 *  Created on: September 19, 2025
 *      Author: Issac (RscnDvlJo)
 */
 
#ifndef ROBOTDESCRIPTION_H_
#define ROBOTDESCRIPTION_H_



#include "ros/ros.h"
#include "sensor_msgs/JointState.h"

#include <moveit/move_group_interface/move_group_interface.h>

#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_visual_tools/moveit_visual_tools.h>


struct TrajectoryParams {
	std::string planning_group;
	moveit::planning_interface::MoveGroupInterface move_group_interface;
	const moveit::core::JointModelGroup* joint_model_group;
	moveit::core::RobotStatePtr state;

	TrajectoryParams(const std::string& group);

	bool initialize();
};

class RobotDescription{
	private :
		sensor_msgs::JointState m_joint_state;
		TrajectoryParams m_trajectoryParams;
		trajectory_msgs::JointTrajectory m_joint_traj;


		
		robot_model_loader::RobotModelLoader m_robot_model_loader;
		robot_model::RobotModelPtr m_robot_model;


		
	public :
		RobotDescription();
		~RobotDescription();
		
		bool initialize();
		
		sensor_msgs::JointState* ret_joint_state();
		trajectory_msgs::JointTrajectory* ret_joint_traj();
		TrajectoryParams* trajectoryParams();
		robot_state::RobotState* ret_kinematic_state();       
		
		
};



	
#endif
