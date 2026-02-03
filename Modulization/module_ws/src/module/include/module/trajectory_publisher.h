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

#include <moveit_visual_tools/moveit_visual_tools.h>

#include <string>

class TrajectoryPublisher{
	private:
		ros::Publisher m_display_pub;
		moveit_visual_tools::MoveItVisualTools m_visual_tools;


	public:
		TrajectoryPublisher(ros::NodeHandle&, const std::string&);
		~TrajectoryPublisher();


		void publish(const moveit_msgs::RobotTrajectory&);
		void waitForNext(const std::string&);
};

#endif

