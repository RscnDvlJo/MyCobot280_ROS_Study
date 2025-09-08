/*
 * sphere_path_planning.h
 *
 *  Created on: August 4, 2025
 *      Author: Issac (RscnDvlJo)
 */


#ifndef SPHERE_PATH_PLANNIG_H_
#define SPHERE_PATH_PLANNIG_H_

#include "ros/ros.h"
#include "setting.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <cmath>


#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/planning_scene/planning_scene.h>
#include <moveit/planning_pipeline/planning_pipeline.h>
#include <moveit/kinematic_constraints/utils.h>
#include <moveit/robot_trajectory/robot_trajectory.h>
#include <moveit/planning_interface/planning_interface.h>
#include <moveit/robot_state/conversions.h>

#include <moveit/trajectory_processing/iterative_time_parameterization.h>

#include <moveit_msgs/RobotTrajectory.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include <geometry_msgs/Pose.h>


struct PlannerConfig{
	std::string group_name;
	std::string ee_link;
	double pos_tol = 1e-3;
	double rot_tol = 1e-2;
	double allowed_time = 2.0;


};


class SpherePathPlanning{
	private:

		double m_radius;
		double m_x, m_y, m_z; 
		double m_dist;
		
		int m_pathsize;
	
		Eigen::Matrix3d m_rotMat;
		Eigen::Matrix3d m_robotRotMat;

		Eigen::MatrixXd m_robotQuaternion;
		Eigen::MatrixXd m_robotJointPath;

		Eigen::MatrixXd m_path; 
		Eigen::Vector3d m_x_unit_vec;
		
		
		robot_model_loader::RobotModelLoader m_loader;
		robot_model::RobotModelPtr m_model;
		planning_scene::PlanningScenePtr m_scene;
		planning_pipeline::PlanningPipelinePtr m_pipeline;
		
		PlannerConfig* m_cfg;
		
	public:
		SpherePathPlanning(double, double, double, double, double, PlannerConfig*);
		~SpherePathPlanning();

		void genPathNPose(moveit_msgs::RobotTrajectory&, moveit_msgs::RobotState&);
		

		
		void calcTempRotMat(double, double);
		void calcTempRobotRotMat(double, double);
		
		void calcRobotQuaternion(Eigen::Matrix3d, int);
		
		void doInverseKinematics();
		
		
		std::vector<geometry_msgs::Pose> makeWaypoints();
		void setPlanningPrt(PlannerConfig*);
		bool doPlanning(PlannerConfig, std::vector<geometry_msgs::Pose>, moveit_msgs::RobotTrajectory&, moveit_msgs::RobotState&);
		
		void calcTargetJointAngle();


		Eigen::MatrixXd* reqJointPath();
		int reqPathSize();
};



#endif
