#include "ros/ros.h"
#include "adhoc_communication/SendPointCloud.h"
#include <cstdlib>
#include <string>
#include <sensor_msgs/PointCloud2.h>

void send_ptcloud(sensor_msgs::PointCloud2 cloud)
{
  ROS_INFO("inside");
  ros::NodeHandle n;
  std::string robot_prefix = "";
  std::string node_prefix = "/adhoc_communication/";
  ros::ServiceClient client = n.serviceClient<adhoc_communication::SendPointCloud>(robot_prefix + node_prefix + "send_pointcloud");
  adhoc_communication::SendPointCloud srv;
  srv.request.dst_robot = "Turtlebot-H";
  srv.request.topic = "/rtabmap/cloud_map";
  srv.request.cloud = cloud;
  if (client.call(srv))
  {
    ROS_INFO("Status: %ld", (long int)srv.response.status);
  }
  else
  {
    ROS_ERROR("Failed to call service SendPointCloud");
   // return 1;
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "send_pointcloud_client");
  if (argc != 1)
  {
    ROS_INFO("usage: not correct number of arguments");
    return 1;
  }

  ros::NodeHandle nh;
  ros::Rate rate(20);

  ros::Subscriber sub = nh.subscribe<sensor_msgs::PointCloud2>("/rtabmap/cloud_map",1,send_ptcloud);
  
  ROS_INFO("here");
  ros::spin ();
  //return 0;
}

