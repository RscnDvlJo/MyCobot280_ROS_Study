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
#include "module/trajectory_manager.h"

class PathPlanner{
	private:
		PathPlannerConfig& m_pathConfig;

		Eigen::Vector3d m_center{0,0,0};
		Eigen::Vector3d m_unit_vec{0,0,1};

		double m_radius;
		double m_dist;

		Eigen::Matrix3d m_rotMat;
		Eigen::Matrix3d m_robotRotMat;

		Eigen::Matrix3d m_rotMat_phi;
		Eigen::Matrix3d m_rotMat_theta;
		Eigen::Matrix3d m_rotMat_spin;

		// ===== 내부 helper =====
		void calcTempRotMat(double phi, double theta);
		void calcTempRobotRotMat();
		Eigen::Quaterniond calcRobotQuaternion(int);
		Eigen::Quaterniond m_q_prev;


	public:
		explicit PathPlanner(PathPlannerConfig&);
		~PathPlanner();

		PathData genPathNPose();
	};


#endif
