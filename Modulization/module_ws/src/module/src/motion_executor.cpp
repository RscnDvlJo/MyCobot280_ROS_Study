/*
 * motion_executor.cpp
 *
 *  Created on: Febraury 03, 2026
 *      Author: Issac (RscnDvlJo)
 */


#include "module/motion_executor.h"

MotionExecutor::MotionExecutor(moveit::planning_interface::MoveGroupInterface& _mgi, TrajectoryManager& _tjmanager, TrajectoryPublisher& _tjpublish)
: m_mgi(_mgi), m_tjmanager(_tjmanager), m_tjpublish(_tjpublish)
{

}

MotionExecutor::~MotionExecutor(){

}

void MotionExecutor::goToReadyPose(){
	
	// const std::string& group_name = m_mgi.getName();

	
	m_mgi.setStartStateToCurrentState();

	
	if (!m_mgi.setNamedTarget("ready")) {
		ROS_ERROR("[MotionExecutor] Failed to set named target: ready");
		return;
	}

	moveit::planning_interface::MoveGroupInterface::Plan _plan;
	bool success = (m_mgi.plan(_plan) ==
	moveit::planning_interface::MoveItErrorCode::SUCCESS);

	if (!success) {
		ROS_ERROR("[MotionExecutor] Planning to ready pose failed");
		return;
	}

	
	m_tjpublish.publish(_plan.trajectory_);
	m_tjpublish.waitForNext("Go to READY pose");

	
	m_mgi.execute(_plan);


}

void MotionExecutor::executeMotion(){

	const auto& _path = m_tjmanager.jointPath();

	if (_path.size() < 2) return;


	// m_mgi.setStartStateToCurrentState();
    const auto* jmg =
        m_mgi.getCurrentState()->getJointModelGroup(m_mgi.getName());

	moveit::core::RobotState current_state(*m_mgi.getCurrentState());
	
	for (size_t i = 0; i + 1 < _path.size(); ++i) {

		// moveit::core::RobotState start_state(m_mgi.getRobotModel());
		m_mgi.setStartStateToCurrentState();
		m_mgi.setJointValueTarget(_path[i + 1]);
		

		/* 
		start_state.setJointGroupPositions(
		    m_mgi.getCurrentState()->getJointModelGroup(m_mgi.getName()),
		    _path[i]);
		m_mgi.setStartState(start_state);
		*/
		/*
		const auto& _q_goal  = _path[i + 1];
		m_mgi.setJointValueTarget(_q_goal);
		*/
		
		moveit::planning_interface::MoveGroupInterface::Plan _plan;
		bool _success = (m_mgi.plan(_plan) ==
				moveit::planning_interface::MoveItErrorCode::SUCCESS);

		if (!_success) {
			ROS_WARN_STREAM("[MotionExecutor] Plan failed at segment " << i);
			continue;
		}

		m_tjpublish.publish(_plan.trajectory_);

		m_tjpublish.waitForNext("Segment " + std::to_string(i) + " → " + std::to_string(i + 1));
		
		m_mgi.execute(_plan);
		moveit::core::RobotState new_state(*m_mgi.getCurrentState());
		new_state.setJointGroupPositions(jmg, _path[i + 1]);
		m_mgi.setStartState(new_state);



		
	}
}
