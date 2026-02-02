/*
 * motion_planner.h
 *
 *  Created on: February 2, 2026
 *      Author: Issac (RscnDvlJo)
 */

#ifndef MODULE_MOTIONPLANNER_H_
#define MODULE_MOTIONPLANNER_H_

#pragma once


#include "trajectory_manager.h"
#include "ik_solver.h"
#include "state_handler.h"

#include <moveit/robot_state/robot_state.h>  
#include <moveit/robot_model/robot_model.h>   

#include <moveit/move_group_interface/move_group_interface.h>

class MotionPlanner{
   private:
      TrajectoryManager& m_tjmanager;
      IKSolver& m_ikSolver;
      StateHandler& m_stthdl;
      RobotContext& m_rbctxt;

   public:
      explicit MotionPlanner(TrajectoryManager&, IKSolver&, StateHandler&, RobotContext&);
      ~MotionPlanner();

      std::vector<std::vector<double>> genJointPath();

};

#endif

