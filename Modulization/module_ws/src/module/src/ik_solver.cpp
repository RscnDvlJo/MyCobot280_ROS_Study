/*
 * ik_solver.cpp
 *
 *  Created on: January 15, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
#include "module/ik_solver.h"
 
IKSolver::IKSolver(IKConfig& _iKConfig, RobotContext& _robotContext, moveit::core::RobotState& _robotState):
m_iKConfig(_iKConfig), m_robotContext(_robotContext), m_robot_state(_robotState)
{
    
	m_free_ik_count = m_iKConfig.free_ik_count;

	m_timeout_free = m_iKConfig.timeout_free;
	m_timeout_retry = m_iKConfig.timeout_retry;
	m_timeout_strict = m_iKConfig.timeout_strict;

	m_ignore_collision = m_iKConfig.ignore_collision;

	m_kqo = m_iKConfig.kqo;

	m_relaxed_limits = m_iKConfig.relaxed_limits;


	// m_robot_state = m_robotContext.robot_state;
	// m_stateHandler.robot_state_candidate;
	m_jmg = m_robotContext.jmg;

	
	
	m_validity_cb = nullptr;


	m_tip_link = m_robotContext.mgi.getEndEffectorLink();
}

IKSolver::~IKSolver(){

}

bool IKSolver::solveIK(std::vector<geometry_msgs::Pose>& _pose){
	m_robot_state.setJointGroupPositions(m_jmg, m_relaxed_limits.data());

	const auto* _model = m_robot_state.getRobotModel().get();
	const auto& _var_names = m_jmg->getVariableNames();

	int _count = 1;
	// m_stateHandler.current_count;
	bool _found = false;

	kinematics::KinematicsQueryOptions _kqo_free = m_kqo;
	kinematics::KinematicsQueryOptions _kqo_cons = m_kqo;
	kinematics::KinematicsQueryOptions _kqo_rel  = m_kqo; 

	_kqo_rel.return_approximate_solution = true;

	robot_state::GroupStateValidityCallbackFn m_validity_cb =
		[](moveit::core::RobotState*, const moveit::core::JointModelGroup*, const double*) {
		return true;
	};

	// 1) FREE IK
	if (_count <= m_free_ik_count) {


	_found = m_robot_state.setFromIK(m_jmg, _pose, m_tip_link, m_timeout_free, m_validity_cb, _kqo_free);

	#ifdef ROS_BUILD
	  ROS_WARN_STREAM("[FREE IK] waypoint " << _count << (_found ? " o" : " x"));
	#endif
	}

	// 2) CONSISTENCY (ramp down)
	if (!_found) {
		auto _cons = makeRampedConsistency(m_jmg, _count);
		_found = m_robot_state.setFromIK(m_jmg, _pose, m_tip_link, _cons, m_timeout_strict, m_validity_cb, _kqo_cons);
		#ifdef ROS_BUILD
			double _avg = _cons.empty() ? 0.0 : std::accumulate(_cons.begin(), _cons.end(), 0.0)/_cons.size();
			ROS_WARN_STREAM("[CONSISTENCY IK] waypoint " << _count << " lim(avg)≈" << _avg << (_found ? " o" : " x"));
		#endif
	}

	// 3) RELAXED (approx allow + Relaxed consistency + longer timeout)
	if (!_found) {
		auto _cons_relaxed = makeConsistencyVec(_jmg,
		m_relaxed_limits[0], m_relaxed_limits[1], m_relaxed_limits[2],
		m_relaxed_limits[3], m_relaxed_limits[4], m_relaxed_limits[5]);
		_found = m_robot_state.setFromIK(m_jmg, _pose, m_tip_link, _cons_relaxed, m_timeout_retry, m_validity_cb, _kqo_rel);
		#ifdef ROS_BUILD
			ROS_WARN_STREAM("[RELAXED IK] waypoint " << count << (_found ? " o" : " x"));
		#endif
	}


	// No result
	if (!_found) return false;

	// Get result
	m_robot_state.copyJointGroupPositions(m_jmg, joint_values);


	// remapping solution near to previous solution

	for (size_t vi = 0; vi < out_joint_values.size(); ++vi) {
		const std::string& var_name = var_names[vi];
		const moveit::core::JointModel* jm = model->getJointOfVariable(var_name);   // get joint model which joint name belong


		// joint type must be revolute & continuous
		if (jm && jm->getType() == moveit::core::JointModel::REVOLUTE) {
			const auto* rjm = static_cast<const moveit::core::RevoluteJointModel*>(jm);
			if (rjm->isContinuous()) {
				double delta = angles::shortest_angular_distance(prev_solution[vi], out_joint_values[vi]);
				out_joint_values[vi] = prev_solution[vi] + delta;
			}
		}
	}
	
	if(_found)	return true;
	else		return false;
	


}
