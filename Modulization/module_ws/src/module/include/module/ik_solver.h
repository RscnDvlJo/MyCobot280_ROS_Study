/*
 * ik_solver.h
 *
 *  Created on: January 15, 2026
 *      Author: Issac (RscnDvlJo)
 */


#include "config.h"
#include "robot_context.h"
#include "state_handler.h"


class IKSolver{
	private:
		IKConfig& m_iKConfig;
		RobotContext& m_robotContext;


		moveit::core::RobotState& m_robot_state;
		const moveit::core::JointModelGroup* m_jmg;
		std::string m_tip_link;

		int m_free_ik_count;

		double m_timeout_free;
		double m_timeout_strict;
		double m_timeout_retry;

		bool m_ignore_collision;
		robot_state::GroupStateValidityCallbackFn m_validity_cb;

		kinematics::KinematicsQueryOptions m_kqo;

		std::array<double, 6> m_relaxed_limits;


	public:
		IKSolver(IKConfig&, RobotContext&, moveit::core::RobotState& );
		~IKSolver();

		bool solveIK(std::vector<geometry_msgs::Pose>&);

};
