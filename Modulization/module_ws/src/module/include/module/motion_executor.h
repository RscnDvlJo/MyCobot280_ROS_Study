/*
 * motion_executor.h
 *
 *  Created on: Febraury 03, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
#ifndef MODULE_MOTION_EXECUTOR_H
#define MODULE_MOTION_EXECUTOR_H


#include <vector>

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_msgs/RobotTrajectory.h>

#include "trajectory_manager.h"
#include "trajectory_publisher.h"
#include "robot_context.h"
#include "state_handler.h"
#include "state_publisher.h"


class MotionExecutor{

	private:
		moveit::planning_interface::MoveGroupInterface& m_mgi;
		TrajectoryManager& m_tjmanager;
		TrajectoryPublisher& m_tjpublish;
		RobotContext& m_rbctxt;
		StateHandler& m_stthdl;
		StatePublisher& m_sttpub;
		
		void commitCurrentStateFromMoveIt(const moveit_msgs::RobotTrajectory&);
		
		Eigen::Affine3d getReadyTargetPose(moveit::planning_interface::MoveGroupInterface::Plan);
		
	public:

		explicit MotionExecutor(moveit::planning_interface::MoveGroupInterface&,
			   TrajectoryManager&,
			   TrajectoryPublisher&,
			   RobotContext&,
			   StateHandler&,
			   StatePublisher&);
		~MotionExecutor();

		void goToReadyPose();
		void executeMotion();
};
#endif

