// src/joint_state_broadcaster.cpp
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <unordered_map>

int main(int argc, char** argv) {
  ros::init(argc, argv, "joint_state_broadcaster");
  ros::NodeHandle nh, pnh("~");


  std::vector<std::string> joint_names = {
    "joint2_to_joint1",
    "joint3_to_joint2",
    "joint4_to_joint3",
    "joint5_to_joint4",
    "joint6_to_joint5",
    "joint6output_to_joint6"
  };
  pnh.getParam("joint_names", joint_names);


  std::vector<double> positions(joint_names.size(), 0.0);
  std::unordered_map<std::string, size_t> name_to_idx;
  for (size_t i = 0; i < joint_names.size(); ++i) name_to_idx[joint_names[i]] = i;


  ros::Publisher js_pub = nh.advertise<sensor_msgs::JointState>("/joint_states", 10);


  auto cmd_cb = [&](const sensor_msgs::JointState::ConstPtr& msg) {

    if (!msg->name.empty()) {
      for (size_t k = 0; k < msg->name.size(); ++k) {
        auto it = name_to_idx.find(msg->name[k]);
        if (it != name_to_idx.end()) {
          size_t idx = it->second;
          if (k < msg->position.size()) positions[idx] = msg->position[k];
        }
      }
    } else {

      for (size_t i = 0; i < positions.size() && i < msg->position.size(); ++i) {
        positions[i] = msg->position[i];
      }
    }
  };
  ros::Subscriber cmd_sub = nh.subscribe<sensor_msgs::JointState>("/joint_state_cmd", 10, cmd_cb);

  // publish period
  double rate_hz = 50.0;
  pnh.getParam("rate_hz", rate_hz);
  ros::Rate rate(rate_hz);

  while (ros::ok()) {
    sensor_msgs::JointState js;
    js.header.stamp = ros::Time::now();
    js.name = joint_names;
    js.position = positions;
    js_pub.publish(js);

    ros::spinOnce();
    rate.sleep();
  }
  return 0;
}

