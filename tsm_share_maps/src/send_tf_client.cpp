#include "ros/ros.h"
#include "adhoc_communication/SendTf.h"
#include <cstdlib>
#include <string>
#include <tf2_msgs/TFMessage.h>

void send_tf2(tf2_msgs::TFMessage tf)
{
  ROS_INFO("inside");
  ros::NodeHandle n;
  std::string robot_prefix = "";
  std::string node_prefix = "/adhoc_communication/";
  ros::ServiceClient client = n.serviceClient<adhoc_communication::SendTf>(robot_prefix + node_prefix + "send_tf");
  adhoc_communication::SendTf srv;
  srv.request.dst_robot = "Turtlebot-H";
  srv.request.topic = "/tf_Turtle";
  srv.request.tf = tf;
  if (client.call(srv))
  {
    ROS_INFO("Status: %ld", (long int)srv.response.status);
  }
  else
  {
    ROS_ERROR("Failed to call service SendTf");
   // return 1;
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "send_tf_client");
  if (argc != 1)
  {
    ROS_INFO("usage: not correct number of arguments");
    return 1;
  }

  ros::NodeHandle nh;
  ros::Rate rate(20);

  ros::Subscriber sub = nh.subscribe<tf2_msgs::TFMessage>("/tf",1,send_tf2);
  
  ROS_INFO("here");
  ros::spin ();
  //return 0;
}

