/*
 * system_descriptor.cpp
 *
 *  Created on: July 1, 2025
 *      Author: Issac (RscnDvlJo)
 */


#include "modular_code/system_descriptor.h"



RobotDescription::RobotDescription(){
	

}

RobotDescription::~RobotDescription(){


}



void RobotDescription::setJointName(){
	// In the future, the joint names will be passed as parameters
	// In this time, those are just namae of mycobot280's joint
	m_joint_state.name = {

		"joint2_to_joint1",
		"joint3_to_joint2",
		"joint4_to_joint3",
		"joint5_to_joint4",
		"joint6_to_joint5",
		"joint6output_to_joint6"
	};
}

void RobotDescription::initJointPos(){
    	m_joint_state.position = std::vector<double>(6, 0.0);

}

sensor_msgs::JointState* RobotDescription::return_joint_state(){
	return &m_joint_state;
}



ObjectDescription::ObjectDescription(){

}

ObjectDescription::~ObjectDescription(){

}


void ObjectDescription::initObject(float _xc, float _yc, float _zc, float _r, float _p, float _y){


	m_transform.setOrigin(tf::Vector3(_xc, _yc, _zc));
	m_q.setRPY(_r, _p, _y);
	m_transform.setRotation(m_q);
	
	m_br.sendTransform(tf::StampedTransform(m_transform, ros::Time::now(), "g_base", "dome"));

}
