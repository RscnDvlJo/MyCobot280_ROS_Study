/*
 * trajectory_manager.h
 *
 *  Created on: January 27, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 
#ifndef MODULE_TRAJECTORY_MANAGER_H_
#define MODULE_TRAJECTORY_MANAGER_H_

#include <geometry_msgs/Pose.h>

#include <vector>
#include <utility>
#include <cstddef>


struct PathData{
	std::vector<geometry_msgs::Pose> waypoints;
};

class TrajectoryManager{
	private:
		PathData m_pathData;
		size_t m_current_idx{0};
		
	public:
		TrajectoryManager();
		~TrajectoryManager();

		// 1) Path 주입 (초기화)
		void setPath(PathData&&);

		// 2) 상태 조회
		bool empty() const;
		size_t size() const;
		size_t index() const;

		// 3) 현재 waypoint 접근
		const geometry_msgs::Pose& current() const;

		// 4) 진행 제어
		bool hasNext() const;
		void advance();
		void reset();

};


#endif
