#include "ros/ros.h"
#include "sensor_msgs/JointState.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "cobot_joint_setting");
    ros::NodeHandle nh;

    ros::Publisher joint_pub = nh.advertise<sensor_msgs::JointState>("mycobot_280/joint_states", 10);

    ros::Rate loop_rate(10);  // 10 Hz

    sensor_msgs::JointState joint_state;
    joint_state.name = {
        "joint2_to_joint1",
        "joint3_to_joint2",
        "joint4_to_joint3",
        "joint5_to_joint4",
        "joint6_to_joint5",
        "joint6output_to_joint6"
    };

    joint_state.position = {
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0
    };

    while (ros::ok())
    {
        joint_state.header.stamp = ros::Time::now();
        joint_pub.publish(joint_state);
        loop_rate.sleep();
    }

    return 0;
}
