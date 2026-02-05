/*
 * motion_optimizer.cpp
 *
 *  Created on: Febraury 04, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
#include "module/motion_optimizer.h"


MotionOptimizer::MotionOptimizer(const moveit::core::RobotModelPtr& _robot_model, RobotContext& _rbctxt, BasicConfig& _basicConfig, StateHandler& _stthdl, IKSolver& _ikSolver, TrajectoryManager& _tjmanager)
: m_robot_state(_robot_model), m_rbctxt(_rbctxt), m_stthdl(_stthdl), m_ikSolver(_ikSolver), m_tjmanager(_tjmanager)
{
	m_robot_state.setToDefaultValues();     // It is not related to the robot state of stthdl
	ROS_INFO("[MotionOptimizer Initialized]");

	m_rail_joint_name = _basicConfig.linear_rail_joint_name;
}

double MotionOptimizer::evaluateJCondNum(double _rail_pos)
{
	double _cost = 0.0;
	
	m_robot_state.setVariablePosition(m_rail_joint_name, _rail_pos);
	
	std::vector<double> _seed;
	m_ikSolver.makeReadyStateSeed(m_robot_state, _seed);   // jmg is automatically setted as jmg_only_robot

	while (m_tjmanager.hasNext()) {

		const geometry_msgs::Pose& _target_pose = m_tjmanager.current();

		// IK (RobotState를 직접 갱신)
		bool _ok = m_ikSolver.solveIK(_target_pose, m_robot_state, _seed);
		if (!_ok) {
			_cost += 1e6;   // IK 실패 패널티
			m_tjmanager.advance();
			continue;
		}
		else {
			m_robot_state.copyJointGroupPositions(m_rbctxt.jmg_only_robot, _seed);

			// Jacobian 계산
			Eigen::MatrixXd _J;
			m_robot_state.getJacobian(
			m_rbctxt.jmg_only_robot,
			m_robot_state.getLinkModel(
			(m_rbctxt.jmg_only_robot)->getLinkModelNames().back()
			),
			Eigen::Vector3d::Zero(),
			_J
			);

			// Jacobian condition number
			Eigen::JacobiSVD<Eigen::MatrixXd> svd(_J);
			const auto& _s = svd.singularValues();
			double _s_min = std::max(_s.tail(1)(0), 1e-6);
			double _cond = _s(0) / _s_min;

			_cost += _cond;
		}

		m_tjmanager.advance();
	}

	return _cost;
}


double MotionOptimizer::optimizeGlobal(double _rail_min, double _rail_max, size_t _num_samples){
	ROS_INFO_STREAM("[MotionOptimizer] Global optimize rail in ["<< _rail_min << ", " << _rail_max << "] samples=" << _num_samples);

	double _best_rail = _rail_min;
	double _best_cost = std::numeric_limits<double>::infinity();

	if (_num_samples < 2) {
		ROS_WARN("[MotionOptimizer] num_samples < 2, fallback");
		return _rail_min;
	}

	const double _step = (_rail_max - _rail_min) /static_cast<double>(_num_samples - 1);

	for (size_t i = 0; i < _num_samples; ++i) {

		double _rail = _rail_min + _step * static_cast<double>(i);

		double _cost = evaluateJCondNum(_rail);

		ROS_DEBUG_STREAM("[MotionOptimizer] rail=" << _rail << " cost=" << _cost);

		if (_cost < _best_cost) {
			_best_cost = _cost;
			_best_rail = _rail;
		}
	}

	ROS_INFO_STREAM("[MotionOptimizer] Global best rail=" << _best_rail << " cost=" << _best_cost);

	m_tjmanager.reset();

	return _best_rail;
}

