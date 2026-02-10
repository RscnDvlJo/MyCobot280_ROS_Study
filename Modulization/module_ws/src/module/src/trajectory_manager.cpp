/*
 * trajectory_manager.cpp
 *
 *  Created on: January 27, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 
#include "module/trajectory_manager.h"

TrajectoryManager::TrajectoryManager(){

}
TrajectoryManager::~TrajectoryManager(){

}

void TrajectoryManager::setPath(PathData&& _path){
	m_pathData = std::move(_path);
	m_current_idx = 0;
}

void TrajectoryManager::setJointPath(const JointTrajectoryData& path) {
	m_jointPath = path;
}


bool TrajectoryManager::empty() const{
	return m_pathData.waypoints.empty();
}

size_t TrajectoryManager::size() const{
	return m_pathData.waypoints.size();
}

size_t TrajectoryManager::index() const{
	return m_current_idx;
}

bool TrajectoryManager::hasNext() const{

	return (m_current_idx + 1) < m_pathData.waypoints.size();
	// return m_current_idx < m_pathData.waypoints.size();
}

const geometry_msgs::Pose& TrajectoryManager::current() const{
	if (m_current_idx >= m_pathData.waypoints.size()) {
		throw std::out_of_range(
		"TrajectoryManager::current() index out of range");
	}
	return m_pathData.waypoints[m_current_idx];


	// return m_pathData.waypoints.at(m_current_idx);
}

const JointTrajectoryData& TrajectoryManager::jointPath() const
{
	return m_jointPath;
}

const std::vector<geometry_msgs::Pose>&
TrajectoryManager::waypointPath() const
{
    	return m_pathData.waypoints;  
}


void TrajectoryManager::advance(){
	if (hasNext()) {
		++m_current_idx;
	}
}

void TrajectoryManager::reset(){
	m_current_idx = 0;
}
