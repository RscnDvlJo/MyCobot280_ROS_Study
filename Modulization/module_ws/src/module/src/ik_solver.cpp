/*
 * ik_solver.cpp
 *
 *  Created on: January 15, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
#include "module/ik_solver.h"
 
IKSolver::IKSolver(IKConfig& _iKConfig, RobotContext& _robotContext, StateHandler& _stateHandler, const moveit::core::GroupStateValidityCallbackFn& _validity_cb):
m_iKConfig(_iKConfig), m_robotContext(_robotContext), m_stateHandler(_stateHandler), m_robot_state(m_stateHandler.candidateRobotState()), m_jmg(m_robotContext.jmg_only_robot), m_validity_cb(_validity_cb)
{
    
	m_free_ik_count = m_iKConfig.free_ik_count;

	m_timeout_free = m_iKConfig.timeout_free;
	m_timeout_retry = m_iKConfig.timeout_retry;
	m_timeout_strict = m_iKConfig.timeout_strict;

	m_ignore_collision = m_iKConfig.ignore_collision;

	m_kqo = m_iKConfig.kqo;

	m_relaxed_limits = m_iKConfig.relaxed_limits;

	m_attempts_free = m_iKConfig.attempts_free;
	m_attempts_strict = m_iKConfig.attempts_strict;
	m_attempts_retry = m_iKConfig.attempts_retry;
	
	m_tip_link = (m_robotContext.jmg_only_robot)->getLinkModelNames().back();
}


IKSolver::~IKSolver(){

}

void IKSolver::makeReadyStateSeed(moveit::core::RobotState& _robot_state, std::vector<double>& _seed){

	_robot_state.setToDefaultValues(m_jmg, "ready");
	_robot_state.copyJointGroupPositions(m_jmg, _seed);

}

void IKSolver::makeCurrentStateSeed(moveit::core::RobotState& _robot_state, std::vector<double> _seed){
   
	_robot_state.copyJointGroupPositions(m_jmg, _seed);
	// m_robot_state.setJointGroupPositions(m_jmg, _seed);

}




bool IKSolver::solveIK(const geometry_msgs::Pose& _target_pose, moveit::core::RobotState& _robot_state, const std::vector<double>& _seed){
	// m_robot_state.setJointGroupPositions(m_jmg, m_relaxed_limits.data());
	
	
	Eigen::Isometry3d _target_eig;
	tf2::fromMsg(_target_pose, _target_eig);
    


	// m_robot_state.setJointGroupPositions(m_jmg, m_stateHandler.prevJointState());
	/*
	std::vector<double> joint_vals;
	_robot_state.copyJointGroupPositions(m_jmg, joint_vals);
	
	m_robot_state.setJointGroupPositions(m_jmg, joint_vals);
	*/
	
	_robot_state.setJointGroupPositions(m_jmg, _seed);
	_robot_state.update();


	
	const auto* _model = _robot_state.getRobotModel().get();
	const auto& _var_names = m_jmg->getVariableNames();

	int _count = m_stateHandler.currentIKCount();
	


	// m_stateHandler.current_count;
	bool _found = false;

	kinematics::KinematicsQueryOptions _kqo_free = m_kqo;
	kinematics::KinematicsQueryOptions _kqo_cons = m_kqo;
	kinematics::KinematicsQueryOptions _kqo_rel  = m_kqo; 

	_kqo_rel.return_approximate_solution = true;
	
	
	
	/*
	robot_state::GroupStateValidityCallbackFn m_validity_cb =
		[](moveit::core::RobotState*, const moveit::core::JointModelGroup*, const double*) {
		return true;
	};
	*/
	
	
	// 1) FREE IK
	if (_count <= m_free_ik_count) {


		// _found = m_robot_state.setFromIK(m_jmg, _target_pose, m_tip_link, m_attempts_free, m_timeout_free, m_validity_cb, _kqo_free);
		_found = _robot_state.setFromIK(m_jmg, _target_pose, m_tip_link, m_timeout_free, m_validity_cb, _kqo_free);
		#ifdef ROS_BUILD
			ROS_WARN_STREAM("[FREE IK] waypoint " << _count << (_found ? " o" : " x"));
		#endif
		
		ROS_INFO_STREAM("free");
		
	}

	// 2) CONSISTENCY (ramp down)
	if (!_found) {
		auto _cons = makeRampedConsistency(m_jmg, _count);
		// _found = m_robot_state.setFromIK(m_jmg, _target_eig, m_tip_link, _cons, m_attempts_strict, m_timeout_strict, m_validity_cb, _kqo_cons);
		_found = _robot_state.setFromIK(m_jmg, _target_eig, m_tip_link, _cons, m_timeout_strict, m_validity_cb, _kqo_cons);
		#ifdef ROS_BUILD
			double _avg = _cons.empty() ? 0.0 : std::accumulate(_cons.begin(), _cons.end(), 0.0)/_cons.size();
			ROS_WARN_STREAM("[CONSISTENCY IK] waypoint " << _count << " lim(avg)≈" << _avg << (_found ? " o" : " x"));
		#endif
		
		ROS_INFO_STREAM("consis");
	}

	// 3) RELAXED (approx allow + Relaxed consistency + longer timeout)
	if (!_found) {
		auto _cons_relaxed = makeConsistencyVec(m_jmg,
		m_relaxed_limits[0], m_relaxed_limits[1], m_relaxed_limits[2],
		m_relaxed_limits[3], m_relaxed_limits[4], m_relaxed_limits[5]);
		// _found = m_robot_state.setFromIK(m_jmg, _target_eig, m_tip_link,  _cons_relaxed,m_attempts_retry, m_timeout_retry, m_validity_cb, _kqo_rel);
		_found = _robot_state.setFromIK(m_jmg, _target_eig, m_tip_link,  _cons_relaxed, m_timeout_retry, m_validity_cb, _kqo_rel);
		#ifdef ROS_BUILD
			ROS_WARN_STREAM("[RELAXED IK] waypoint " << count << (_found ? " o" : " x"));
		#endif
		
		ROS_INFO_STREAM("relax");
	}


	// No result
	if (!_found) return false;

	std::vector<double> _cand;
	_robot_state.copyJointGroupPositions(m_jmg, _cand);
	
	const auto& _prev = _seed;
	// const auto& _prev = m_stateHandler.prevJointState();
	    
	    
	// remapping solution near to previous solution

	for (size_t vi = 0; vi < _cand.size(); ++vi) {
		const std::string& _var_name = _var_names[vi];
		const moveit::core::JointModel* _jm = _model->getJointOfVariable(_var_name);   // get joint model which joint name belong


		// joint type must be revolute & continuous
		if (_jm && _jm->getType() == moveit::core::JointModel::REVOLUTE) {
			const auto* _rjm = static_cast<const moveit::core::RevoluteJointModel*>(_jm);
			if (_rjm->isContinuous()) {
				double _delta = angles::shortest_angular_distance(_prev[vi], _cand[vi]);
				_cand[vi] = _prev[vi] + _delta;
			}
		}
	}

	std::ostringstream oss;
	oss << "[IK RESULT] WP " << m_stateHandler.currentIKCount() << " : ";
	for (double q : _cand)
	    oss << q << " ";
	ROS_INFO_STREAM(oss.str());

		if(_found){
			_robot_state.setJointGroupPositions(m_jmg, _cand);
			_robot_state.enforceBounds();
			_robot_state.update();


			m_stateHandler.upIKCount();
			m_stateHandler.snapshotCandidateJoints();
			
			return true;
		}
		else		return false;
		
	}


std::vector<double> IKSolver::makeConsistencyVec(const moveit::core::JointModelGroup* _jmg, double _base_lim, double _shoulder_lim, double _elbow_lim, double _wrist1_lim,double _wrist2_lim, double _wrist3_lim) const{
	const auto& _vars = _jmg->getVariableNames();
	std::vector<double> _v(_vars.size(), 0.6);   // default consistency

	for (size_t k = 0; k < _vars.size(); ++k) {
		const std::string& n = _vars[k];

		if      (n.find("joint1") != std::string::npos)
			_v[k] = _base_lim;
		else if (n.find("joint2") != std::string::npos)
			_v[k] = _shoulder_lim;
		else if (n.find("joint3") != std::string::npos)
			_v[k] = _elbow_lim;
		else if (n.find("joint4") != std::string::npos)
			_v[k] = _wrist1_lim;
		else if (n.find("joint5") != std::string::npos)
			_v[k] = _wrist2_lim;
		else if (n.find("joint6") != std::string::npos)
			_v[k] = _wrist3_lim;
		}

	return _v;
}


std::vector<double> IKSolver::makeRampedConsistency(const moveit::core::JointModelGroup* _jmg, size_t _waypoint_idx) const
{
	double _t = 0.0;

	if (_waypoint_idx > static_cast<size_t>(m_free_ik_count)) {
		size_t j = _waypoint_idx - m_free_ik_count;
		_t = std::min(1.0, static_cast<double>(j) / 10.0);  // 10-step ramp
	}

	double _base  = (1.0 - _t) * 0.8 + _t * 0.35;
	double _sh    = (1.0 - _t) * 0.8 + _t * 0.35;
	double _elbow = (1.0 - _t) * 1.0 + _t * 0.5;
	double _w1    = (1.0 - _t) * 1.2 + _t * 0.6;
	double _w2    = (1.0 - _t) * 1.2 + _t * 0.6;
	double _w3    = (1.0 - _t) * 1.2 + _t * 0.6;

	return makeConsistencyVec(_jmg, _base, _sh, _elbow, _w1, _w2, _w3);
}

