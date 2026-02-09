/*
 * trajectory_publisher.h
 *
 *  Created on: Febraury 03, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
#ifndef MODULE_TRAJECTORY_PUBLISHER_H
#define MODULE_TRAJECTORY_PUBLISHER_H

#include <ros/ros.h>

#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/RobotTrajectory.h>
#include <moveit/robot_state/conversions.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

#include <string>
#include "state_handler.h"


class TrajectoryPublisher{
	private:
		ros::Publisher m_display_pub;
		moveit_visual_tools::MoveItVisualTools m_visual_tools;
		StateHandler& m_stthdl;

	public:
		TrajectoryPublisher(ros::NodeHandle&, const std::string&, StateHandler&);
		~TrajectoryPublisher();


		void publish(const moveit_msgs::RobotTrajectory&);
		void waitForNext(const std::string&);
};

#endif

