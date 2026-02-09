/*
 * trajectory_publisher.cpp
 *
 *  Created on: Febraury 03, 2026
 *      Author: Issac (RscnDvlJo)
 */

#include "module/trajectory_publisher.h"

TrajectoryPublisher::TrajectoryPublisher(ros::NodeHandle& _nh, const std::string& _base_frame, StateHandler& _stthdl)
: m_visual_tools(_base_frame), m_stthdl(_stthdl)
{
	m_display_pub = _nh.advertise<moveit_msgs::DisplayTrajectory>("/display_planned_path", 1, true);

	m_visual_tools.loadRobotStatePub("/display_robot_state");
	m_visual_tools.deleteAllMarkers();
	m_visual_tools.trigger();

	ROS_INFO("[TrajectoryPublisher] Initialized");


}

TrajectoryPublisher::~TrajectoryPublisher(){

}

void TrajectoryPublisher::publish(const moveit_msgs::RobotTrajectory& _traj)
{
	moveit_msgs::DisplayTrajectory _display_msg;

	_display_msg.model_id = m_visual_tools.getRobotModel()->getName();
	_display_msg.trajectory.clear();
	_display_msg.trajectory.push_back(_traj);

	// moveit::core::robotStateToRobotStateMsg(*m_visual_tools.getCurrentState(), _display_msg.trajectory_start);      // it is neccesary to define start state of trajectory
	moveit::core::robotStateToRobotStateMsg(m_stthdl.currentRobotState(), _display_msg.trajectory_start);
	m_display_pub.publish(_display_msg);

	ROS_INFO("[TrajectoryPublisher] DisplayTrajectory published");
}

void TrajectoryPublisher::waitForNext(const std::string& _msg)
{
	ROS_INFO_STREAM("[TrajectoryPublisher] Waiting: " << _msg);

	m_visual_tools.prompt(_msg);

	ROS_INFO("[TrajectoryPublisher] Next pressed");
}


