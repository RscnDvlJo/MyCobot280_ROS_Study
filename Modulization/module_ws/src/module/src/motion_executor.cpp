/*
 * motion_executor.cpp
 *
 *  Created on: Febraury 03, 2026
 *      Author: Issac (RscnDvlJo)
 */


#include "module/motion_executor.h"

MotionExecutor::MotionExecutor(moveit::planning_interface::MoveGroupInterface& _mgi, TrajectoryManager& _tjmanager, TrajectoryPublisher& _tjpublish, RobotContext& _rbctxt, StateHandler& _stthdl, StatePublisher& _sttpub)
: m_mgi(_mgi), m_tjmanager(_tjmanager), m_tjpublish(_tjpublish), m_rbctxt(_rbctxt), m_stthdl(_stthdl), m_sttpub(_sttpub)
{

}

MotionExecutor::~MotionExecutor(){

}

void MotionExecutor::goToReadyPose(){
	
	
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



	m_tjpublish.publish(_plan.trajectory_, getReadyTargetPose(_plan));
	m_tjpublish.waitForNext("Go to READY pose");

	
	// m_sttpub.disable();
	auto _result = m_mgi.execute(_plan);
	if (_result != moveit::planning_interface::MoveItErrorCode::SUCCESS) {
		ROS_ERROR("Execution failed");
		return;
	}
	// ros::Duration(2.0).sleep();   


	// commitCurrentStateFromMoveIt(_plan.trajectory_);
	
	// m_sttpub.enable();


}

void MotionExecutor::executeMotion(){

	const auto& _path = m_tjmanager.jointPath();
	const auto& _waypoint_path = m_tjmanager.waypointPath();


	if (_path.size() < 2) return;

	// moveit::core::RobotState current_state(*m_mgi.getCurrentState());

	for (size_t i = 0; i + 1 < _path.size(); ++i) {

		moveit::core::RobotState _start_state(*m_mgi.getCurrentState());                     	// stthdl.currentRobotState
		_start_state.setJointGroupPositions(m_rbctxt.jmg_only_robot, m_stthdl.prevJointState());   // prev_solution is reset in motion generating process


		m_mgi.setStartState(_start_state);                                    
		m_mgi.setJointValueTarget(_path[i]);     
		
		
		moveit::planning_interface::MoveGroupInterface::Plan _plan;
		bool _success = (m_mgi.plan(_plan) ==
		moveit::planning_interface::MoveItErrorCode::SUCCESS);

		if (!_success) {
			ROS_WARN_STREAM("[MotionExecutor] Plan failed at segment " << i);
			continue;
		}

		Eigen::Affine3d target_pose;
		tf2::fromMsg(_waypoint_path[i], target_pose);


		
		m_tjpublish.publish(_plan.trajectory_, target_pose);

		m_tjpublish.waitForNext("Segment " + std::to_string(i) + " → " + std::to_string(i + 1));

		// m_sttpub.disable();

		auto _result = m_mgi.execute(_plan);
		if (_result != moveit::planning_interface::MoveItErrorCode::SUCCESS) {
			ROS_ERROR("Execution failed");
			return;
		}

		commitTargetPoint(_path[i]);

		// m_sttpub.enable();
	}
}

void MotionExecutor::commitTargetPoint(const std::vector<double>& _q)
{
	m_stthdl.currentJointState() = _q;
}

Eigen::Affine3d MotionExecutor::getReadyTargetPose(moveit::planning_interface::MoveGroupInterface::Plan _plan)
{

	Eigen::Affine3d ready_pose = Eigen::Affine3d::Identity();

	const auto& _traj = _plan.trajectory_.joint_trajectory;

	if (_traj.points.empty()) {
		ROS_ERROR("[MotionExecutor] Trajectory has no points");
		return ready_pose;
	}

	const auto& _last_point = _traj.points.back();

	moveit::core::RobotState state(*m_mgi.getCurrentState());

	state.setJointGroupPositions(m_rbctxt.jmg_only_robot, _last_point.positions);

	const std::string& _ee_link = m_mgi.getEndEffectorLink();
	ready_pose = state.getGlobalLinkTransform(_ee_link);

	return ready_pose;
}

