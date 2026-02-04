/*
 * motion_planner.cpp
 *
 *  Created on: February 2, 2026
 *      Author: Issac (RscnDvlJo)
 */

#include "module/motion_planner.h"

MotionPlanner::MotionPlanner(TrajectoryManager& _tjmanager, IKSolver& _ikSolver, StateHandler& _stthdl, RobotContext& _rbctxt)
: m_tjmanager(_tjmanager), m_ikSolver(_ikSolver), m_stthdl(_stthdl), m_rbctxt(_rbctxt)
{

}

MotionPlanner::~MotionPlanner(){

}

std::vector<std::vector<double>> MotionPlanner::genJointPath(){

	std::vector<std::vector<double>> _joint_path;

	moveit::core::RobotState& _robot_state = m_stthdl.currentRobotState(); 
	bool ok = _robot_state.setFromIK(m_rbctxt.jmg_only_robot, m_tjmanager.current(), 0.2);

	if (!ok) {
		ROS_ERROR("IK failed at waypoint 0");
		return {};
	}

	_robot_state.copyJointGroupPositions(m_rbctxt.jmg_only_robot, m_stthdl.prevJointState());   // first seed is generated
	m_tjmanager.advance();                                                      // index upcount in waypoints

	std::string _tip_link = (m_rbctxt.mgi).getEndEffectorLink();

	// if there is no tip link, use last link as tip
	if (_tip_link.empty()) {
		const auto& _links = (m_rbctxt.jmg_only_robot)->getLinkModelNames();
		_tip_link = _links.empty() ? "" : _links.back();
	}


	while(1){


		if(!m_ikSolver.solveIK(m_tjmanager.current(), m_stthdl.candidateRobotState(), m_stthdl.prevJointState())){
			/* if solveIK successed, current_robot_state in StateHandler will be updated 
			joint values must be stored in this function using updated current_robot_state
			*/

			/* if solveIK failed, ROS Warning is automatically occured in IKSolver class */
			ROS_WARN("IK failed at waypoint %zu", m_tjmanager.index());
			m_stthdl.resetCandidate();

			break;

		}
		
		m_stthdl.setCandidateFromRobotState(m_rbctxt.jmg_only_robot);   // joint_state_candidate is parsed from robot_state_candidate
		m_stthdl.commitCandidate();                              // joint_state_current is parsed from joint_state_candidate
		m_stthdl.snapshotCurrentJoints();                        // joint_state_pre is parsed from joint_state_cur

		_joint_path.push_back(m_stthdl.currentJointState());


		if(m_tjmanager.hasNext())   m_tjmanager.advance();
		else   break;

	}

	m_tjmanager.reset();
	return _joint_path;

}
