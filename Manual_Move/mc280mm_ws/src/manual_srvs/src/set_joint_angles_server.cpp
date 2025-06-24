#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "manual_srvs/SetJointAngles.h"

ros::Publisher joint_pub;



bool set_angles(manual_srvs::SetJointAngles::Request &req,
                manual_srvs::SetJointAngles::Response &res)
{
    if (req.angles.size() != 6) {
        ROS_WARN("Expected 6 joint angles, got %lu", req.angles.size());
        res.success = false;
        return true;
    }

    sensor_msgs::JointState joint_state;
    joint_state.header.stamp = ros::Time::now();

    joint_state.name = {
        "joint2_to_joint1",
        "joint3_to_joint2",
        "joint4_to_joint3",
        "joint5_to_joint4",
        "joint6_to_joint5",
        "joint6_output"
    };
    joint_state.position = std::vector<double>(req.angles.begin(), req.angles.end());

    joint_pub.publish(joint_state);
    res.success = true;
    ROS_INFO("Joint angles published.");
    return true;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "set_joint_angles_server");
    ros::NodeHandle nh;

    joint_pub = nh.advertise<sensor_msgs::JointState>("joint_states", 10);
    ros::ServiceServer service = nh.advertiseService("set_joint_angles", set_angles);

    ROS_INFO("Service [set_joint_angles] is ready.");
    ros::spin();
    return 0;
}
