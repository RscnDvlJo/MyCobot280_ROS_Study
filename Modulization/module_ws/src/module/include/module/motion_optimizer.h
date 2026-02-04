/*
 * motion_optimizer.h
 *
 *  Created on: Febraury 04, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 
#ifndef MODULE_MOTION_OPTIMIZER_H_
#define MODULE_MOTION_OPTIMIZER_H_

#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <ros/ros.h>
#include <limits>

#include "ik_solver.h"
#include "trajectory_manager.h"
#include "robot_context.h"
#include "config.h"
#include "state_handler.h"


class MotionOptimizer {
	private:
		moveit::core::RobotState m_robot_state;
		RobotContext& m_rbctxt;


		StateHandler& m_stthdl;
		IKSolver& m_ikSolver;
		TrajectoryManager& m_tjmanager;

		std::string m_rail_joint_name;

	public:
		explicit MotionOptimizer(const moveit::core::RobotModelPtr&, RobotContext&, BasicConfig&, StateHandler&, IKSolver&, TrajectoryManager&);
		~MotionOptimizer();

		double evaluateJCondNum(double);
		double optimizeGlobal(double, double, size_t);
};

#endif
