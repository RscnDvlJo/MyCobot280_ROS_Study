/*
 * state_publisher.cpp
 *
 *  Created on: January 27, 2026
 *      Author: Issac (RscnDvlJo)
 */
 


#include "module/state_publisher.h"


StatePublisher::StatePublisher(ros::NodeHandle& _nh, const moveit::core::JointModelGroup* _jmg, double _publish_rate_hz, StateHandler& _stthdl)
	:m_stthdl(_stthdl){
	m_joint_pub = _nh.advertise<sensor_msgs::JointState>("joint_states", 10);
	m_joint_names = _jmg->getVariableNames();
	m_rail_pos = 0.0;

	m_timer = _nh.createTimer(ros::Duration(1.0/_publish_rate_hz), &StatePublisher::timerCallback, this);
}

void StatePublisher::publishJointState(double _rail_pos){
	sensor_msgs::JointState _js;
	_js.header.stamp = ros::Time::now();
	_js.name = m_joint_names;

	_js.position.resize(m_joint_names.size());

	_js.position[6] = _rail_pos;

	auto& _arm = m_stthdl.currentJointState();
	for (size_t i = 0; i < _arm.size(); ++i)
		_js.position[i + 1] = _arm[i];

	m_joint_pub.publish(_js);

}

void StatePublisher::updateJointState(double _rail_pos){
	m_rail_pos = _rail_pos;
}

void StatePublisher::timerCallback(const ros::TimerEvent&){
	// if (!m_stthdl) return;

	sensor_msgs::JointState _js;
	_js.header.stamp = ros::Time::now();
	_js.name = m_joint_names;
	_js.position.resize(m_joint_names.size());

	_js.position[6] = m_rail_pos;

	auto& arm = m_stthdl.currentJointState();
	for (size_t i = 0; i < arm.size(); ++i)
		_js.position[i + 1] = arm[i];

	m_joint_pub.publish(_js);

}


