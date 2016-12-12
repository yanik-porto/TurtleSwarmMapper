#include "ros/ros.h"
#include "adhoc_communication/ChangeMCMembership.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "change_mc_membership_client");
  if (argc != 3)
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<adhoc_communication::ChangeMCMembership>("join_mc_group");
  adhoc_communication::ChangeMCMembership srv;
  srv.request.group_name = argv[1];
  srv.request.action = atoi(argv[2]);
  if (client.call(srv))
  {
    ROS_INFO("Sum: %ld", (long int)srv.response.status);
  }
  else
  {
    ROS_ERROR("Failed to call service ChangeMCMembership");
    return 1;
  }

  return 0;
}
