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



	size_t dof = (rbcontext.jmg_only_robot)->getVariableCount();
	StateHandler stthdl(rbcontext.robot_model, dof);
	
	StatePublisher sttpub(nh, rbcontext.jmg_robot_with_rail, 30, stthdl);		// Publisher

	moveit::core::GroupStateValidityCallbackFn validity_cb =
		[](moveit::core::RobotState* rs,
			const moveit::core::JointModelGroup* jmg,
			const double* values)
	{
		return true;  // or collision check
	};


	IKSolver ikSolver(
		*config.ikConfig(),
		rbcontext,
		stthdl,
		validity_cb
	);
	
	PathPlanner pathplan(*config.pathPlannerConfig());

	TrajectoryManager tjmanager;
	tjmanager.setPath(pathplan.genPathNPose());


	MotionPlanner motionplan(tjmanager, ikSolver, stthdl, rbcontext);
	tjmanager.setJointPath(motionplan.genJointPath());

	TrajectoryPublisher traj_pub(
		nh,
		rbcontext.robot_model->getModelFrame(),
		stthdl
	);

	MotionExecutor executor(
		rbcontext.mgi,
		tjmanager,
		traj_pub,
		rbcontext,
		stthdl,
		sttpub
	);
	
	traj_pub.waitForNext("initial wait");
	
	executor.goToReadyPose();
	
	
	traj_pub.waitForNext("wanna execute motion?");
	executor.executeMotion();   

	
	ros::waitForShutdown();
}
