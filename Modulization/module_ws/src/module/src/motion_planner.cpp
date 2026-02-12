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

	m_stthdl.initializeSolution();      // cur, prev, candidate are initialized as (0,0,0,0,0,0)
	   
	
	while(1){
	      const auto& _pose = m_tjmanager.current();

	      ROS_INFO_STREAM(
		 "[TARGET POSE] idx " << m_tjmanager.index()
		 << " | Pos("
		 << _pose.position.x << ", "
		 << _pose.position.y << ", "
		 << _pose.position.z << ") "
		 << "Ori("
		 << _pose.orientation.x << ", "
		 << _pose.orientation.y << ", "
		 << _pose.orientation.z << ", "
		 << _pose.orientation.w << ")"
	      );

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
		// m_stthdl.commitCandidate();                              // joint_state_current is parsed from joint_state_candidate
		// m_stthdl.snapshotCurrentJoints();                        // joint_state_pre is parsed from joint_state_cur
		m_stthdl.snapshotCandidateJoints(); 
      		
      		
		_joint_path.push_back(m_stthdl.candidateJointState());


		if(m_tjmanager.hasNext())   m_tjmanager.advance();
		else   break;

	}
	
	ROS_INFO("Generated joint path size: %zu", _joint_path.size());

	for (size_t i = 0; i < _joint_path.size(); ++i) {
	    std::ostringstream oss;
	    oss << "Waypoint " << i << " joints: ";
	    for (double q : _joint_path[i]) {
		oss << q << " ";
	    }
	    ROS_INFO_STREAM(oss.str());
	}

	m_stthdl.resetPrevSolution();
	
	m_tjmanager.reset();
	return _joint_path;

}
