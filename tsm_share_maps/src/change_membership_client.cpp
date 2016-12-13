#include "ros/ros.h"
#include "adhoc_communication/ChangeMCMembership.h"
#include <cstdlib>
#include <string>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "change_mc_membership_client");
  if (argc != 5)
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
  }

  ros::NodeHandle n;
  std::string robot_prefix = argv[1];
  std::string node_prefix = argv[2];
  ros::ServiceClient client = n.serviceClient<adhoc_communication::ChangeMCMembership>(robot_prefix + node_prefix + "join_mc_group");
  adhoc_communication::ChangeMCMembership srv;
  srv.request.group_name = argv[3];
  srv.request.action = atoi(argv[4]);
  if (client.call(srv))
  {
    ROS_INFO("Status: %ld", (long int)srv.response.status);
  }
  else
  {
    ROS_ERROR("Failed to call service ChangeMCMembership");
    return 1;
  }

  return 0;
}
