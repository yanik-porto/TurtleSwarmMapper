
#include <ros/ros.h>
   #include <move_base_msgs/MoveBaseAction.h>
   #include <actionlib/client/simple_action_client.h>
   
   typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
   
   int main(int argc, char** argv){
     ros::init(argc, argv, "navigation_goals");
   
     //tell the action client that we want to spin a thread by default
     MoveBaseClient ac("move_base", true);
   
     //wait for the action server to come up
     while(!ac.waitForServer(ros::Duration(5.0))){
       ROS_INFO("Waiting for the move_base action server to come up");
     }
   
     move_base_msgs::MoveBaseGoal goal;
   
     //we'll send a goal to the robot to move 1 meter forward
     
     
     int i = 0;
     while(i<50){
     goal.target_pose.header.frame_id = "base_link";
     goal.target_pose.header.stamp = ros::Time::now();
     goal.target_pose.pose.position.x = 0.3;
     goal.target_pose.pose.position.y = 0.0;
     goal.target_pose.pose.position.z = 0.0;
     goal.target_pose.pose.orientation.w = 1.0;
     goal.target_pose.pose.orientation.x = 0.0;
     goal.target_pose.pose.orientation.y = 0.0;
     goal.target_pose.pose.orientation.z = 0.0;
  
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);
  
    ac.waitForResult();
 
   if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
     ROS_INFO("Hooray, the base moved 1 meter forward");
   else{
     goal.target_pose.header.frame_id = "base_link";
     goal.target_pose.header.stamp = ros::Time::now();
     goal.target_pose.pose.position.x = 0.0;
     goal.target_pose.pose.position.y = 0.0;
     goal.target_pose.pose.position.z = 0.0;
     goal.target_pose.pose.orientation.w = 1.0;
     goal.target_pose.pose.orientation.x = 0.0;
     goal.target_pose.pose.orientation.y = 0.0;
     goal.target_pose.pose.orientation.z = 0.6;
     ROS_INFO("Sending goal");
     ac.sendGoal(goal);
  
    ac.waitForResult();}
     i = i+1;
  }
   return 0;
 }



