/*
 * config.h
 *
 *  Created on: January 13, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 
#ifndef MODULE_SETTING_H_
#define MODULE_SETTING_H_

#include <string>

#define PI 3.141592653589793


struct BasicConfig{
	std::string group_name;
};


struct PathPlannerConfig{

	double pos_tol;
	double rot_tol;
	double allowed_time;
	
	double theta_shift;
	double theta_move;		

	double phi_shift;
	double phi_move;	
	
	double num_angle_theta;
	double num_angle_phi;		


};

class Config{


	private:
		BasicConfig m_basicConfig;
		PathPlannerConfig m_pathPlannerConfig;
	
	
	public:
		Config();
		~Config();
		
		BasicConfig *basicConfig();
		PathPlannerConfig *pathPlannerConfig();

};

#endif
