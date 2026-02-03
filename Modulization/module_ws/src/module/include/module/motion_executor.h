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

#include "module/trajectory_manager.h"
#include "module/trajectory_publisher.h"

class MotionExecutor{

	private:
		moveit::planning_interface::MoveGroupInterface& m_mgi;
		TrajectoryManager& m_tjmanager;
		TrajectoryPublisher& m_tjpublish;

	public:

		explicit MotionExecutor(moveit::planning_interface::MoveGroupInterface&,
			   TrajectoryManager&,
			   TrajectoryPublisher&);
		~MotionExecutor();

		void executeMotion();
};
#endif

