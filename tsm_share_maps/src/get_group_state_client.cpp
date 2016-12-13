#include "ros/ros.h"
#include "adhoc_communication/GetGroupState.h"
#include <cstdlib>
#include <string>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "get_group_state_client");
  if (argc != 4)
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
  }

  ros::NodeHandle n;
  std::string robot_prefix = argv[1];
  std::string node_prefix = argv[2];
  ros::ServiceClient client = n.serviceClient<adhoc_communication::GetGroupState>(robot_prefix + node_prefix + "get_group_state");
  adhoc_communication::GetGroupState srv;
  srv.request.group_name = argv[3];
  //srv.request.action = atoi(argv[2]);
  if (client.call(srv))
  {
    ROS_INFO("Member: %ld", (long int)srv.response.member);
  }
  else
  {
    ROS_ERROR("Failed to call service GetGroupState");
    return 1;
  }

  return 0;
}
