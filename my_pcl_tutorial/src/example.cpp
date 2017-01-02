#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <tf/transform_listener.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>


ros::Publisher pub;

void 
cloud_cb (const sensor_msgs::PointCloud2 cloud_msg)
{
  // Container for original & filtered data
 // pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; 
 // pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
  //pcl::PCLPointCloud2 transformed_cloud;

  // Convert to PCL data type
  //pcl_conversions::toPCL(*cloud_msg, *cloud);

    //float theta = M_PI/4; // The angle of rotation in radians
  
  // Define a translation of 2.5 meters on the x axis.
  //transform_2.translation() << 2.5, 0.0, 0.0;

  // The same rotation matrix as before; theta radians arround Z axis
 // transform_2.rotate (Eigen::AngleAxisf (theta, Eigen::Vector3f::UnitZ()));

Eigen::Matrix4f transform_1 = Eigen::Matrix4f::Identity(); 
Eigen::Matrix4f transform_2 = Eigen::Matrix4f::Identity();
Eigen::Matrix4f inv_trans = Eigen::Matrix4f::Identity();
Eigen::Matrix4f total = Eigen::Matrix4f::Identity();
// Define a rotation matrix (see https://en.wikipedia.org/wiki/Rotation_matrix)
  float theta1 = 1.47691; // The angle of rotation in radians
  transform_1 (0,0) = cos (theta1);
  transform_1 (0,1) = -sin(theta1);
  transform_1 (1,0) = sin (theta1);
  transform_1 (1,1) = cos (theta1);
  transform_1 (0,3) = 2.466;
  transform_1 (1,3) = 2.482;
  transform_1 (2,3) = 0.0;

  float theta2 = -0.018; // The angle of rotation in radians
  transform_2 (0,0) = cos (theta2);
  transform_2 (0,1) = -sin(theta2);
  transform_2 (1,0) = sin (theta2);
  transform_2 (1,1) = cos (theta2);
  transform_2 (0,3) = 1.575;
  transform_2 (1,3) = -1.903;
  transform_2 (2,3) = 0.0;
  
  inv_trans = transform_2.inverse();
  inv_trans (3,0) = 0;
  inv_trans (3,1) = 0;
  inv_trans (3,2) = 0;
  inv_trans (3,3) = 1;
  total = transform_1*inv_trans;
  sensor_msgs::PointCloud2 output;
  // Perform the actual transformation
  pcl_ros::transformPointCloud (total,cloud_msg, output);

  // Convert to ROS data type
  
  //pcl_conversions::moveFromPCL(transformed_cloud, output);

  // Publish the data
  pub.publish (output);
}
 
int
main (int argc, char** argv)
{

  // Initialize ROS
  ros::init (argc, argv, "my_pcl_tutorial");
  ros::NodeHandle nh;
 
  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe<sensor_msgs::PointCloud2> ("input", 1, cloud_cb);
  tf::TransformListener listener;
  // Create a ROS publisher for the output point cloud
  pub = nh.advertise<sensor_msgs::PointCloud2> ("output", 1);

  // Spin
  ros::spin ();
}
