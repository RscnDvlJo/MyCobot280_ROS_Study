/*
 * setting.h
 *
 *  Created on: August 4, 2025
 *      Author: Issac (RscnDvlJo)
 */


#ifndef SETTING_H_
#define SETTING_H_

#define num_angle_theta 4
#define num_angle_phi 4



// Sphere Path Planning
const double theta_shift = 60;
const double theta_move = 30;		// default 30

const double phi_shift = 180;
const double phi_move = 30;		// default 90

const double PI = 3.141592653589793;
const double tau = 2*PI;


// IK solve parameter
const int FREE_IK_COUNT = 3;			// IK solve w/o consistency
const double TIMEOUT_FREE = 0.20;		// time out for free IK
const double TIMEOUT_STRICT = 0.10;		// time out for consistency IK
const double TIMEOUT_RETRY = 0.50;		// time out for retry IK
const bool  DEBUG_IGNORE_COLLISION = false;	// for debug, if this parameter is true, then ignore collision

extern const std::array<double,6>& relaxed_limits;


#endif
