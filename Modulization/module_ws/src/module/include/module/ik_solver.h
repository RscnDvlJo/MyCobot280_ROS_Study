/*
 * ik_solver.h
 *
 *  Created on: January 15, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
#ifndef MODULE_IK_SOLVER_H
#define MODULE_IK_SOLVER_H

#pragma once

#include "config.h"
#include "robot_context.h"
#include "state_handler.h"
#include <angles/angles.h>

#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2_eigen/tf2_eigen.h>

class IKSolver{
	private:
		IKConfig& m_iKConfig;
		RobotContext& m_robotContext;
		StateHandler& m_stateHandler;

		moveit::core::RobotState& m_robot_state;
		const moveit::core::JointModelGroup* m_jmg;
		std::string m_tip_link;

		int m_free_ik_count;

		unsigned int m_attempts_free;
		unsigned int m_attempts_strict;
		unsigned int m_attempts_retry;

		double m_timeout_free;
		double m_timeout_strict;
		double m_timeout_retry;

		bool m_ignore_collision;
		moveit::core::GroupStateValidityCallbackFn m_validity_cb;

		kinematics::KinematicsQueryOptions m_kqo;
		

		std::array<double, 6> m_relaxed_limits;

		std::vector<double> makeConsistencyVec(const moveit::core::JointModelGroup*, double, double, double, double, double, double) const;


		std::vector<double> makeRampedConsistency(const moveit::core::JointModelGroup*, size_t) const;
        
        
	public:
		IKSolver(IKConfig&, RobotContext&, StateHandler&, const moveit::core::GroupStateValidityCallbackFn&);
		~IKSolver();

		bool solveIK(const geometry_msgs::Pose&, moveit::core::RobotState&, const std::vector<double>&);

};

#endif
