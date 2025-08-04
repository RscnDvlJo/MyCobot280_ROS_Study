/*
 * system_descriptor.h
 *
 *  Created on: July 1, 2025
 *      Author: Issac (RscnDvlJo)
 */


#ifndef SYSTEMDESCRIPTOR_H_
#define SYSTEMDESCRIPTOR_H_

#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "tf/transform_broadcaster.h"

class RobotDescription{
	private:
		sensor_msgs::JointState m_joint_state;
	
	
	
	public:
		RobotDescription();
		~RobotDescription();

		void setJointName();
		void initJointPos();

		
		sensor_msgs::JointState* return_joint_state();

};


class ObjectDescription{
	private:
		tf::Transform m_transform;
		tf::Quaternion m_q;
		tf::TransformBroadcaster m_br;

	
	public:
		ObjectDescription();
		~ObjectDescription();
		
		void initObject(float, float, float, float, float, float);
};

#endif
