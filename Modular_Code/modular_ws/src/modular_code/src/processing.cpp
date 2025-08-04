/*
 * processing.cpp
 *
 *  Created on: July 21, 2025
 *      Author: Issac (RscnDvlJo)
 */


#include "modular_code/processing.h"



int main(int argc, char** argv){


	ros::init(argc, argv, "processing");
	ros::NodeHandle nh;
	
	ros::Publisher joint_pub = nh.advertise<sensor_msgs::JointState>("robot/joint_states", 10);
	
	ros::Rate loop_rate(5);		// 5Hz
	
	
	RobotDescription rbdescrip;
	ObjectDescription ojdescrip;
	// PathPlanning pathplan;
	
	rbdescrip.setJointName();
	rbdescrip.initJointPos();
	

	ojdescrip.initObject(0.25, 0, 0, 0, 0, 0);
	
	// init();
	
	

	while(ros::ok){
	
		rbdescrip.return_joint_state()->header.stamp = ros::Time::now();
		joint_pub.publish(*(rbdescrip.return_joint_state()));
		
		loop_rate.sleep();		// wait until next period
	
	}

	return 0;
}

void init(){


	
	

	

	
	// pathplan.init();
	
}


