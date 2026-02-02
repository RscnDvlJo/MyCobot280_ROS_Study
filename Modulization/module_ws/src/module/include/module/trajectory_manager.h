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


using JointTrajectoryData = std::vector<std::vector<double>>;

/*
struct JointTrajectoryData {
	std::vector<std::vector<double>> joint_path;
};
*/


struct PathData{
	std::vector<geometry_msgs::Pose> waypoints;
};

class TrajectoryManager{
	private:
		PathData m_pathData;
		JointTrajectoryData m_jointPath;
		size_t m_current_idx{0};
		
	public:
		TrajectoryManager();
		~TrajectoryManager();

		void setPath(PathData&&);
		void setJointPath(const JointTrajectoryData& path);

		
		bool empty() const;
		size_t size() const;
		size_t index() const;

		
		const geometry_msgs::Pose& current() const;

		
		bool hasNext() const;
		void advance();
		void reset();

};


#endif
