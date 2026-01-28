/*
 * main.cpp
 *
 *  Created on: January 13, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 #include "module/main.h"
 
 int main(int argc, char** argv){

	
	ros::init(argc, argv, "main");
	ros::AsyncSpinner spinner(2);
	spinner.start();


	ros::NodeHandle nh, pnh("~");
	
	Config config;		// Parameters
	RobotContext rbcontext(config.basicConfig()->group_name_only_robot, config.basicConfig()->group_name_robot_with_rail);		// Robot Properties



	size_t dof = config.jmg_only_robot->getVariableCount();
	StateHandler stthdl(rbcontext.robot_model, dof);
	
	StatePublisher sttpub(nh, rbcontext.jmg_robot_with_rail, 30, stthdl);		// Publisher

	IKSolver(config.ikConfig(), rbcontext, stthdl, [](moveit::core::RobotState*, const moveit::core::JointModelGroup*, const double*) {
		return true;
	};);
	
	
	

	// path planner
	// motion planner (statehandler, ik_solver)
	
	// joint_value_cur 계산이 성공한 경우 sttpub.updateJointState(stthdl, rail_pos)
	
	
	/*
	ros::Publisher joint_pub = nh.advertise<sensor_msgs::JointState>("joint_states", 10);
	ros::Publisher disp_pub = nh.advertise<moveit_msgs::DisplayTrajectory>("move_group/display_planned_path", 1, true);
	
	
	Config config;
	RobotContext RbContext(config.basicConfig()->group_name);
	
	PathPlanner pathPlanner(0.112, 0.350, 0, 0.150, 0.010, *config.pathPlannerConfig());
	
	// 1. do path plan & generate pose
	pathPlanner.genPathNPose();
	std::vector<geometry_msgs::Pose> waypoints = pathPlanner.makeWaypoints();
	*/
	
	
	ros::waitForShutdown();
}
