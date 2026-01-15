/*
 * config.cpp
 *
 *  Created on: January 14, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
#include "module/config.h"
 
 
Config::Config(){
	m_basicConfig.group_name = "arm";
	
	m_pathPlannerConfig.pos_tol = 0.001;
	m_pathPlannerConfig.rot_tol = 0.01;
	m_pathPlannerConfig.allowed_time = 2.0;
	
	m_pathPlannerConfig.theta_shift = 60.0;
	m_pathPlannerConfig.theta_move = 30.0;
	m_pathPlannerConfig.phi_shift = 180.0;
	m_pathPlannerConfig.phi_move = 30.0;
	
	m_pathPlannerConfig.num_angle_theta = 4.0;
	m_pathPlannerConfig.num_angle_phi = 4.0;
	
		
	m_ikConfig.free_ik_count = 5;

	m_ikConfig.timeout_free = 0.2;
	m_ikConfig.timeout_strict = 0.1;
	m_ikConfig.timeout_retry = 0.5;

	m_ikConfig.ignore_collision = false;

	m_ikConfig.kqo.return_approximate_solution = false;

	m_ikConfig.relaxed_limits = { 1.2, 1.2, 1.4, 1.8, 1.8, 1.8};

}

Config::~Config(){
	
}
 

BasicConfig *Config::basicConfig(void){
	return &m_basicConfig;
}


PathPlannerConfig *Config::pathPlannerConfig(void){
	return &m_pathPlannerConfig;
}

IKConfig *Config::ikConfig(void){
	return &m_ikConfig;
}
