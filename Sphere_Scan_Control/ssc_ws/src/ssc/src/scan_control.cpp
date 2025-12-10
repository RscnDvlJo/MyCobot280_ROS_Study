/*
 * scan_control.cpp
 *
 *  Created on: September 11, 2025
 *      Author: Issac (RscnDvlJo)
 */


#include "ssc/scan_control.h"
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <angles/angles.h>
#include <moveit/kinematics_base/kinematics_base.h>
#include <tf2_eigen/tf2_eigen.h>              

#include <numeric>     // std::accumulate
#include <algorithm>   // std::min



void jointStateLoop(const ros::TimerEvent&, RobotDescription*, ros::Publisher*);
void setVisualizer(moveit_visual_tools::MoveItVisualTools&);


std::vector<double> makeConsistencyVec(const moveit::core::JointModelGroup*, double, double, double, double, double, double);
std::vector<double> makeRampedConsistency(const moveit::core::JointModelGroup*, size_t i);


bool solveWaypointIK(
    moveit::core::RobotState&,
    const moveit::core::JointModelGroup*,
    const Eigen::Isometry3d&,
    const std::string&,
    const std::vector<double>&,
    int,
    int,
    double,
    double,
    double,
    const robot_state::GroupStateValidityCallbackFn&,
    const kinematics::KinematicsQueryOptions&,
    const std::function<std::vector<double>(const moveit::core::JointModelGroup*, size_t)>&,
    const std::function<std::vector<double>(const moveit::core::JointModelGroup*, double,double,double,double,double,double)>&,
    const std::array<double,6>&,   // {base, shoulder, elbow, wrist1, wrist2, wrist3}
    std::vector<double>&);



int main(int argc, char** argv){

	
	ros::init(argc, argv, "ssc");
	ros::AsyncSpinner spinner(2);
	spinner.start();


	ros::NodeHandle nh, pnh("~");
	
	ros::Publisher joint_pub = nh.advertise<sensor_msgs::JointState>("joint_states", 10);
	ros::Publisher disp_pub = nh.advertise<moveit_msgs::DisplayTrajectory>("move_group/display_planned_path", 1, true);
	
  	
	
	
	PlannerConfig plancfg;			// parameters for IK (defined in sphere path planning.h)
	RobotDescription rbdscp;		// robot params for publishing (pg, mgi, jmg, ks etc.)
  	
	SpherePathPlanning sphpathplan(0.112, 0.350, 0, 0.150, 0.010, &plancfg);
	

	
	// 1. do path plan & generate pose
	sphpathplan.genPathNPose();
	std::vector<geometry_msgs::Pose> waypoints = sphpathplan.makeWaypoints();
	
	
	// 2. start joint timer to send joint values in rviz
	ros::Timer joint_timer = nh.createTimer(
	    ros::Duration(0.02), // 50Hz
	    boost::bind(&jointStateLoop, _1, &rbdscp, &joint_pub),
	    false   // oneshot = false
	);
	ROS_INFO("Joint timer created");
	

	// 3. check robotmodel is successfully published
	tf2_ros::Buffer tfBuffer;
	tf2_ros::TransformListener tfListener(tfBuffer);


	ROS_INFO("Waiting for g_base TF to be available...");
	bool has_tf = false;
	while (ros::ok() && !has_tf) {
		has_tf = tfBuffer.canTransform("g_base", "joint1", ros::Time(0));
		if (!has_tf) {
			ROS_WARN_THROTTLE(2.0, "g_base -> joint1 TF not yet available...");
			ros::Duration(0.5).sleep();
		}
		}
	ROS_INFO("g_base TF is available. Initializing MoveItVisualTools.");


	// 4. make parameters for trajectory storaging
	rbdscp.trajectoryParams()->initialize();
	rbdscp.initialize();

	trajectory_msgs::JointTrajectory* traj_ptr = rbdscp.ret_joint_traj();
	traj_ptr->joint_names = rbdscp.ret_joint_state()->name;
	traj_ptr->points.clear();
	
	
	// 5. make visual tools and reference frame
	std::shared_ptr<moveit_visual_tools::MoveItVisualTools> visual_tools;
	visual_tools = std::make_shared<moveit_visual_tools::MoveItVisualTools>("g_base");


	setVisualizer(*visual_tools);



	// 6. define parameters for IK solve

	robot_state::RobotState* kin_state = rbdscp.ret_kinematic_state();
	
	if (!kin_state) {
		ROS_ERROR("KinematicState pointer is NULL!");
	} else {
		ROS_INFO("KinematicState is valid. Model has %zu joints.",
		kin_state->getVariableCount());
	}


	auto& mgi = rbdscp.trajectoryParams()->move_group_interface;
	const moveit::core::JointModelGroup* jmg = rbdscp.trajectoryParams()->joint_model_group;
	
	

	robot_state::GroupStateValidityCallbackFn cb_ignore =
		[](moveit::core::RobotState*, const moveit::core::JointModelGroup*, const double*) {
		return true;
	};

	
	kinematics::KinematicsQueryOptions kqo;
	kqo.return_approximate_solution = false;

	


	// 7. Get first point's IK solution and make it as prev solution
	kin_state->setToDefaultValues();
	bool ok0 = kin_state->setFromIK(jmg, waypoints[0], 0.1);
	
	if (!ok0) {
		ROS_ERROR("IK failed at waypoint 0");
		return 0;
	}
	
	std::vector<double> prev_solution;
	kin_state->copyJointGroupPositions(jmg, prev_solution);

	// get tip link
	std::string tip_link = mgi.getEndEffectorLink();
	
	// if there is no tip link, use last link as tip
	if (tip_link.empty()) {
		const auto& links = jmg->getLinkModelNames();
		tip_link = links.empty() ? "" : links.back();
	}


	// 8. IK solve
	const std::array<double,6> relaxed_limits = {1.2, 1.2, 1.4, 1.8, 1.8, 1.8};
	
	for (size_t i = 1; i < waypoints.size(); i++) {
	
	
		const auto& pose = waypoints[i];
		Eigen::Isometry3d pose_eig;
		tf2::fromMsg(pose, pose_eig);

		
		
		ROS_INFO("Waypoint %zu: Position(%.3f, %.3f, %.3f) Orientation(%.3f, %.3f, %.3f, %.3f)",
		     i,
		     pose.position.x, pose.position.y, pose.position.z,
		     pose.orientation.x, pose.orientation.y, 
		     pose.orientation.z, pose.orientation.w);

		if (!jmg) {
			ROS_ERROR("JointModelGroup is NULL!");
			continue;
		}


		robot_state::RobotState* kin_state = rbdscp.ret_kinematic_state();
		if (!kin_state) {
			ROS_ERROR("KinematicState pointer is NULL!");
			break;
		}

		std::vector<double> joint_values(6, 0.0);


		// Solve IK & make continuous solution
		bool ok = solveWaypointIK(
		    *kin_state,        // RobotState&
		    jmg,               // JointModelGroup*
		    pose_eig,          // target pose
		    tip_link,          // tip
		    prev_solution,     // previous solution
		    (int)i,            // waypoint index
		    FREE_IK_COUNT,     // free IK count
		    TIMEOUT_FREE,      // free timeout
		    TIMEOUT_STRICT,    // strict timeout
		    TIMEOUT_RETRY,     // retry timeout
		    cb_ignore,         // validity callback
		    kqo,               // KinematicsQueryOptions
		    makeRampedConsistency, // function reference OK
		    makeConsistencyVec,    // function reference OK
		    relaxed_limits,        // array<double,6>
		    joint_values           // output vector
		);

		if (!ok) {
			ROS_WARN("IK not found for waypoint %zu", i);
			continue;
		}

		



		ROS_INFO("IK Success for waypoint %zu -> [%.3f, %.3f, %.3f, %.3f, %.3f, %.3f]",
		     i, joint_values[0], joint_values[1], joint_values[2],
		     joint_values[3], joint_values[4], joint_values[5]);

		

		{
			auto* js = rbdscp.ret_joint_state();
			js->position = prev_solution;

			ros::Rate rr(100);             // 100Hz
			for (int rep = 0; rep < 10; ++rep) { // about 0.1 sec publish
			js->header.stamp = ros::Time::now();
			joint_pub.publish(*js);
			rr.sleep();
			}
			ros::spinOnce();
		}

		


		moveit::core::RobotState start_state(*mgi.getCurrentState());
		start_state.setJointGroupPositions(jmg, prev_solution);
		
		
		mgi.setStartState(start_state);
		mgi.setJointValueTarget(joint_values);


		moveit::planning_interface::MoveGroupInterface::Plan plan;
		bool planned = (mgi.plan(plan) == moveit::core::MoveItErrorCode::SUCCESS);
		if (!planned) {
			ROS_WARN("Planning failed for waypoint %zu", i);
			continue;
		}

		// make trajectory lines and wait for next button
		visual_tools->publishTrajectoryLine(plan.trajectory_, jmg);
		visual_tools->trigger();
		visual_tools->prompt("Press 'next' to EXECUTE this segment");

	
		
		// 4) execute
		auto exec_rc = mgi.execute(plan);
		if (exec_rc != moveit::core::MoveItErrorCode::SUCCESS) {
			ROS_WARN("Execution failed for waypoint %zu", i);
			continue;
		}


		prev_solution = joint_values;

	}
	ros::waitForShutdown();

}


void jointStateLoop(const ros::TimerEvent&, RobotDescription* rbdscp, ros::Publisher* joint_pub){


	rbdscp->ret_joint_state()->header.stamp = ros::Time::now();
	joint_pub->publish(*(rbdscp->ret_joint_state()));   

}


void setVisualizer(moveit_visual_tools::MoveItVisualTools& visual_tools){
	// first stop before start periodic timer
	// press next button to start timer
	
	
	visual_tools.deleteAllMarkers();
	visual_tools.loadRemoteControl();
	visual_tools.trigger();
	visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to start the demo");	
	
}


std::vector<double> makeConsistencyVec(const moveit::core::JointModelGroup* jmg, double base_lim, double shoulder_lim, double elbow_lim, double wrist1_lim, double wrist2_lim, double wrist3_lim) {
	

	std::vector<double> v(jmg->getVariableCount(), 0.6);
	const auto& vars = jmg->getVariableNames();

									
	for (size_t k = 0; k < vars.size(); ++k) {
		const std::string& n = vars[k];			// n == temporary joint name
		
		// find using name & save weight 
		if      (n.find("joint1") != std::string::npos) 
			v[k] = base_lim;
		else if (n.find("joint2") != std::string::npos) 
			v[k] = shoulder_lim;
		else if (n.find("joint3") != std::string::npos) 
			v[k] = elbow_lim;
		else if (n.find("joint4") != std::string::npos) 
			v[k] = wrist1_lim;
		else if (n.find("joint5") != std::string::npos) 
			v[k] = wrist2_lim;
		else if (n.find("joint6") != std::string::npos) 
			v[k] = wrist3_lim;
		}
		
	return v;
	
};


std::vector<double> makeRampedConsistency(const moveit::core::JointModelGroup* jmg, size_t i) {
	double t = 0.0;
	
	if (i > static_cast<size_t>(FREE_IK_COUNT)) {
		size_t j = i - FREE_IK_COUNT;          // number of waypoint after free ik
		t = std::min(1.0, j / 10.0);           // linear ramp down (10 range)
	}
	
	double base  = (1.0 - t)*0.8 + t*0.35;   // 0.8 → 0.35
	double sh    = (1.0 - t)*0.8 + t*0.35;
	double elbow = (1.0 - t)*1.0 + t*0.5;    // Elbows/wrists are more generous
	double w1    = (1.0 - t)*1.2 + t*0.6;
	double w2    = (1.0 - t)*1.2 + t*0.6;
	double w3    = (1.0 - t)*1.2 + t*0.6;
	
	return makeConsistencyVec(jmg, base, sh, elbow, w1, w2, w3);
};

bool solveWaypointIK(
	moveit::core::RobotState& state,
	const moveit::core::JointModelGroup* jmg,
	const Eigen::Isometry3d& pose_eig,
	const std::string& tip_link,
	const std::vector<double>& prev_solution,
	int i,
	int free_ik_count,
	double timeout_free,
	double timeout_strict,
	double timeout_retry,
	const robot_state::GroupStateValidityCallbackFn& validity_cb,
	const kinematics::KinematicsQueryOptions& kqo,
	const std::function<std::vector<double>(const moveit::core::JointModelGroup*, size_t)>& makeRampedConsistency,
	const std::function<std::vector<double>(const moveit::core::JointModelGroup*, double,double,double,double,double,double)>& makeConsistencyVec,
	const std::array<double,6>& relaxed_limits,   // {base, shoulder, elbow, wrist1, wrist2, wrist3}
	std::vector<double>& out_joint_values)
{
	// Reflect the previous solution to the current state
	state.setJointGroupPositions(jmg, prev_solution);

	const auto* model     = state.getRobotModel().get();
	const auto& var_names = jmg->getVariableNames();

	bool found = false;
	
	kinematics::KinematicsQueryOptions kqo_free = kqo;
	kinematics::KinematicsQueryOptions kqo_cons = kqo;
	kinematics::KinematicsQueryOptions kqo_rel  = kqo; 
	
	kqo_rel.return_approximate_solution = true;

	// 1) FREE IK
	if (i <= free_ik_count) {
		// found = state.setFromIK(jmg, pose_eig, tip_link, timeout_free, DEBUG_IGNORE_COLLISION ? cb_ignore: robot_state::GroupStateValidityCallbackFn(), kqo_free);
		// DEBUG_IGNORE_COLLISION == false == do not ignore collision
		
		found = state.setFromIK(jmg, pose_eig, tip_link, timeout_free, validity_cb, kqo_free);
		
		#ifdef ROS_BUILD
		ROS_WARN_STREAM("[FREE IK] waypoint " << i << (found ? " o" : " x"));
		#endif
	}

	// 2) CONSISTENCY (ramp down)
	if (!found) {
		auto cons = makeRampedConsistency(jmg, i);
		found = state.setFromIK(jmg, pose_eig, tip_link, cons, timeout_strict, validity_cb, kqo_cons);
		#ifdef ROS_BUILD
		double avg = cons.empty() ? 0.0 : std::accumulate(cons.begin(), cons.end(), 0.0)/cons.size();
		ROS_WARN_STREAM("[CONSISTENCY IK] waypoint " << i << " lim(avg)≈" << avg << (found ? " o" : " x"));
		#endif
	}

	// 3) RELAXED (approx allow + Relaxed consistency + longer timeout)
	if (!found) {
		auto cons_relaxed = makeConsistencyVec(jmg,
				   relaxed_limits[0], relaxed_limits[1], relaxed_limits[2],
				   relaxed_limits[3], relaxed_limits[4], relaxed_limits[5]);
		found = state.setFromIK(jmg, pose_eig, tip_link, cons_relaxed, timeout_retry, validity_cb, kqo_rel);
		#ifdef ROS_BUILD
		ROS_WARN_STREAM("[RELAXED IK] waypoint " << i << (found ? " o" : " x"));
		#endif
	}


	// No result
	if (!found) return false;

	// Get result
	state.copyJointGroupPositions(jmg, out_joint_values);

	
	// remapping solution near to previous solution
	
	for (size_t vi = 0; vi < out_joint_values.size(); ++vi) {
		const std::string& var_name = var_names[vi];
		const moveit::core::JointModel* jm = model->getJointOfVariable(var_name);	// get joint model which joint name belong

		
		// joint type must be revolute & continuous
		if (jm && jm->getType() == moveit::core::JointModel::REVOLUTE) {
			const auto* rjm = static_cast<const moveit::core::RevoluteJointModel*>(jm);
			if (rjm->isContinuous()) {
				double delta = angles::shortest_angular_distance(prev_solution[vi], out_joint_values[vi]);
				out_joint_values[vi] = prev_solution[vi] + delta;
			}
		}
	}




	state.setJointGroupPositions(jmg, out_joint_values);
	state.enforceBounds();


	return true;
	

} 

