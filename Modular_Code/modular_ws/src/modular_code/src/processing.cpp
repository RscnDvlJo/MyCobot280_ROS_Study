/*
 * processing.cpp
 *
 *  Created on: July 21, 2025
 *      Author: Issac (RscnDvlJo)
 */


#include "modular_code/processing.h"



int main(int argc, char** argv){

	
	
	ros::init(argc, argv, "processing");
	ros::AsyncSpinner spinner(1);
	spinner.start();
	
	// ros::NodeHandle nh;
	ros::NodeHandle nh, pnh("~");
	
	ros::Publisher joint_pub = nh.advertise<sensor_msgs::JointState>("robot/joint_states", 10);
	ros::Publisher disp_pub = nh.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
	
	
	ros::Rate loop_rate(5);		// 5Hz
	
	processingDone = false;
	
	

	
	RobotDescription rbdescrip;
	ObjectDescription ojdescrip;
	
	PlannerConfig plancfg;
	SpherePathPlanning sphpathplan(0.042, 0.200, 0, 0.100, 0.010, &plancfg);
	
	rbdescrip.setJointName();
	rbdescrip.initJointPos();
	
	moveit_msgs::RobotTrajectory traj_msg;
	moveit_msgs::RobotState start_state_msg;
	
	sphpathplan.genPathNPose(traj_msg, start_state_msg);



	moveit_msgs::DisplayTrajectory disp;
	disp.model_id = "mycobot_280";
	disp.trajectory.push_back(traj_msg);
	disp.trajectory_start = start_state_msg;
	disp_pub.publish(disp);
	
	ROS_INFO("rviz done");
	ros::waitForShutdown();
	return 0;


	/*
	while(ros::ok){
	
		if (processingDone == false){
			rbdescrip.return_joint_state()->header.stamp = ros::Time::now();
			
		
			for (int i = 0; i < sphpathplan.reqPathSize() ; i ++){
				for (int j = 0; j < 6; j++){
					rbdescrip.return_joint_state()->position[j] = (*sphpathplan.reqJointPath())(i,j);
				}
				if (i == sphpathplan.reqPathSize()){
					processingDone = true;
				}
			}
			
			joint_pub.publish(*(rbdescrip.return_joint_state()));
			
			loop_rate.sleep();		// wait until next period
		
		}else{
	
	
			rbdescrip.return_joint_state()->header.stamp = ros::Time::now();
			
			
			
			joint_pub.publish(*(rbdescrip.return_joint_state()));
			
			loop_rate.sleep();		// wait until next period
	
		}

	
	}
	*/

	return 0;
}

void init(){

	// pathplan.init();
	
}


