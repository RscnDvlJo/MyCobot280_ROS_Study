/*
 * state_handler.cpp
 *
 *  Created on: January 23, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 
 
#include "module/state_handler.h"

StateHandler::StateHandler(const moveit::core::RobotModelPtr& _model, size_t _dof):m_rbState(_model), m_joints(_dof)
{
	m_rbState.robot_state_cur.setToDefaultValues();
	m_rbState.robot_state_candidate = m_rbState.robot_state_cur;

	m_rbState.currentIKCount = 0;
}

StateHandler::~StateHandler(){

}

/*
RbState *StateHandler::rbState(){
    return &m_rbState;    
}
*/


moveit::core::RobotState& StateHandler::currentRobotState(){
	return m_rbState.robot_state_cur;
}

moveit::core::RobotState& StateHandler::candidateRobotState(){
    	return m_rbState.robot_state_candidate;
}

std::vector<double>& StateHandler::currentJointState(){
    	return m_joints.joint_state_cur;
}

std::vector<double>& StateHandler::candidateJointState(){
    	return m_joints.joint_state_candidate;
}

std::vector<double>& StateHandler::prevJointState(){
    	return m_joints.joint_state_prev;
}

void StateHandler::resetCandidate(){
	    m_rbState.robot_state_candidate = m_rbState.robot_state_cur;
	    m_joints.joint_state_candidate = m_joints.joint_state_cur;
}

void StateHandler::commitCandidate(){
	    m_rbState.robot_state_cur = m_rbState.robot_state_candidate;
	    m_joints.joint_state_cur = m_joints.joint_state_candidate;
}

void StateHandler::snapshotCurrentJoints(){
    	m_joints.joint_state_prev = m_joints.joint_state_cur;
}


void StateHandler::setCandidateFromRobotState(const moveit::core::JointModelGroup* _jmg){
	m_rbState.robot_state_candidate.copyJointGroupPositions(_jmg, m_joints.joint_state_candidate);
}

int& StateHandler::currentIKCount(){
	return m_rbState.currentIKCount;
}

void StateHandler::setCurrentJointState(const std::vector<double>& _q) {
	std::lock_guard<std::mutex> lock(m_mtx);
	m_joints.joint_state_cur = _q;
}

std::vector<double> StateHandler::getCurrentJointState() {
	std::lock_guard<std::mutex> lock(m_mtx);
	return m_joints.joint_state_cur;
}
