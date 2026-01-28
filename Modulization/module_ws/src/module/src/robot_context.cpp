/*
 * robot_context.cpp
 *
 *  Created on: January 13, 2026
 *      Author: Issac (RscnDvlJo)
 */
 
 
 #include "module/robot_context.h"
 
 /*
RobotContext::RobotContext(const std::string& group): model_loader(std::make_shared<robot_model_loader::RobotModelLoader>("robot_description")),
robot_model(model_loader->getModel()),
mgi(group){
	
	
	robot_state = std::make_shared<moveit::core::RobotState>(robot_model);
	robot_state->setToDefaultValues();
	
	jmg = robot_model->getJointModelGroup(group);


}
*/	


RobotContext::RobotContext(const std::string& _group_r, const std::string& _group_rwr): model_loader(std::make_shared<robot_model_loader::RobotModelLoader>("robot_description")),
robot_model(model_loader->getModel()),
mgi(_group_r){


	jmg_only_robot = robot_model->getJointModelGroup(_group_r);
	jmg_robot_with_rail = robot_model->getJointModelGroup(_group_rwr);

	if (!jmg_only_robot || !jmg_robot_with_rail) {
		throw std::runtime_error("Invalid JointModelGroup name");
	}


}   
