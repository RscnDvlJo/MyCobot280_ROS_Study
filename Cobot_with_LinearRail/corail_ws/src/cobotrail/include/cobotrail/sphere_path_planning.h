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
#include <geometry_msgs/Pose.h>
#include <moveit/robot_model_loader/robot_model_loader.h>



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
		
		
		Eigen::Matrix3d m_rotMat_spin;
		Eigen::Matrix3d m_rotMat_phi;
		Eigen::Matrix3d m_rotMat_theta;

		Eigen::MatrixXd m_robotQuaternion;
		Eigen::MatrixXd m_robotJointPath;

		Eigen::MatrixXd m_path; 
		Eigen::Vector3d m_unit_vec;
		
		
		robot_model_loader::RobotModelLoader m_loader;
	
		
		void calcTempRotMat(double, double);
		void calcTempRobotRotMat();
		
		void calcRobotQuaternion(Eigen::Matrix3d, int);
		
		
		PlannerConfig* m_cfg;
		
	public:
		SpherePathPlanning(double, double, double, double, double, PlannerConfig*);
		~SpherePathPlanning();

		void genPathNPose();
		
    		std::vector<geometry_msgs::Pose> makeWaypoints();


};



#endif
