/*
 * state_handler.h
 *
 *  Created on: January 15, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 
#ifndef MODULE_STATEHANDLER_H_
#define MODULE_STATEHANDLER_H_

#pragma once

#include <moveit/robot_state/robot_state.h>  
#include <moveit/robot_model/robot_model.h>   
#include <mutex>

struct RbState{

	moveit::core::RobotState robot_state_cur;
	moveit::core::RobotState robot_state_candidate;

	int currentIKCount;
	
	explicit RbState(const moveit::core::RobotModelPtr& _model)
		:robot_state_cur(_model), robot_state_candidate(_model)
	{}
};


struct JointVals{
	std::vector<double> joint_state_cur;
	std::vector<double> joint_state_candidate;
	std::vector<double> joint_state_prev;

	explicit JointVals(size_t dof = 0) 
	:joint_state_cur(dof, 0.0), joint_state_candidate(dof, 0.0), joint_state_prev(dof, 0.0)
	{}
};


class StateHandler{
	
	private:
		RbState m_rbState;
		JointVals m_joints;
		std::mutex m_mtx;
	
	public:
	
		explicit StateHandler(const moveit::core::RobotModelPtr&, size_t );
		~StateHandler();


		// RbState *rbState();     // 직접 접근
		moveit::core::RobotState& currentRobotState();      // StateHandler.currentRobotState() = desired robot state; not commonly used
		moveit::core::RobotState& candidateRobotState();    // StateHandler.candidateRobotState() = desired robot state;

		std::vector<double>& currentJointState();           // StateHandler.currentJointState() = desired joint value; not commonly used
		std::vector<double>& candidateJointState();         // StateHandler.candidateJointState() = desired joint value;
		std::vector<double>& prevJointState();              // StateHandler.prevJointState() = desired joint value; not commonly used


		void resetCandidate();
		void commitCandidate();
		void snapshotCurrentJoints();
	
		void setCandidateFromRobotState(const moveit::core::JointModelGroup*);
		
		int& currentIKCount();
		
		std::vector<double> getCurrentJointState();
      		void setCurrentJointState(const std::vector<double>& _q);

};


#endif
