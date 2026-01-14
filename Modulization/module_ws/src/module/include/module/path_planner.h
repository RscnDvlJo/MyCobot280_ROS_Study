/*
 * path_planner.h
 *
 *  Created on: January 13, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 
#ifndef MODULE_PATH_PLANNER_H_
#define MODULE_PATH_PLANNER_H_


#include "ros/ros.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <cmath>
#include <geometry_msgs/Pose.h>


#include "module/config.h"

class PathPlanner{

	private:
		double m_radius;
		double m_x, m_y, m_z; 
		double m_dist;
		
		double m_theta_shift;
		double m_theta_move;
		
		double m_phi_shift;
		double m_phi_move;
		
		double m_num_angle_theta;
		double m_num_angle_phi;
		
		
		int m_pathsize;
	
		Eigen::Matrix3d m_rotMat;
		Eigen::Matrix3d m_robotRotMat;
		
		
		Eigen::Matrix3d m_rotMat_spin;
		Eigen::Matrix3d m_rotMat_phi;
		Eigen::Matrix3d m_rotMat_theta;

		Eigen::MatrixXd m_robotQuaternion;
		Eigen::MatrixXd m_robotJointPath;

		Eigen::MatrixXd m_path; 
		Eigen::Vector3d m_unit_vec;
		
	
		PathPlannerConfig& m_pathPlannerConfig;
		// Config& m_config;
		
		void calcTempRotMat(double, double);
		void calcTempRobotRotMat();
		
		void calcRobotQuaternion(Eigen::Matrix3d, int);
	
	public:
		PathPlanner(double, double, double, double, double, PathPlannerConfig&);
		~PathPlanner();

		void genPathNPose();
		std::vector<geometry_msgs::Pose> makeWaypoints();
};


#endif
