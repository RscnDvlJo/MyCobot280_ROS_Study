/*
 * state_publisher.h
 *
 *  Created on: January 27, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 
#ifndef MODULE_ROBOT_STATEPUBLISHER_H_
#define MODULE_ROBOT_STATEPUBLISHER_H_

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <moveit/robot_model/joint_model_group.h>

#include <vector>
#include <string>

#include "module/state_handler.h"

class StatePublisher{
	private:
		ros::Publisher m_joint_pub;
		ros::Timer m_timer;

		std::vector<std::string> m_joint_names;

		StateHandler& m_stthdl;  // observer
		double m_rail_pos;

		bool _enable{true};

		void timerCallback(const ros::TimerEvent&);

	public:
		explicit StatePublisher(ros::NodeHandle&, const moveit::core::JointModelGroup*, double, StateHandler&);
		~StatePublisher();


		void publishJointState( double);
		void updateJointState(double);
		
		void enable(){_enable = true;};
		void disable(){_enable = false;};
};

#endif
