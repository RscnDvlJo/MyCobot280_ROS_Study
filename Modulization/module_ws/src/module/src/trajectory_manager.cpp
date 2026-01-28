/*
 * trajectory_manager.cpp
 *
 *  Created on: January 27, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 
#include "module/trajectory_manager.h"


void TrajectoryManager::setPath(PathData&& _path){
	m_pathData = std::move(_path);
	m_current_idx = 0;
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
	return m_current_idx < m_pathData.waypoints.size();
}

const geometry_msgs::Pose& TrajectoryManager::current() const{
	return m_pathData.waypoints.at(m_current_idx);
}

void TrajectoryManager::advance(){
	if (hasNext()) {
		++m_current_idx;
	}
}

void TrajectoryManager::reset(){
	m_current_idx = 0;
}
