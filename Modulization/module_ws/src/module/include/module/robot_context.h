/*
 * robot_context.h
 *
 *  Created on: January 13, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 
#ifndef MODULE_ROBOT_CONTEXT_H_
#define MODULE_ROBOT_CONTEXT_H_

#include <string>
#include <memory>

#include "ros/ros.h"
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>


struct RobotContext{

	RobotContext() = default;
	explicit RobotContext(const std::string& group);


	robot_model_loader::RobotModelLoaderPtr model_loader;
	moveit::core::RobotModelPtr robot_model;
	
	moveit::core::RobotStatePtr robot_state;
	const moveit::core::JointModelGroup* jmg;
	
	moveit::planning_interface::MoveGroupInterface mgi;
};

#endif
