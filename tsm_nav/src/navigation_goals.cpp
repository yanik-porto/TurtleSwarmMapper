
#include <ros/ros.h>
#include <tf/transform_listener.h>
   #include <move_base_msgs/MoveBaseAction.h>
   #include <actionlib/client/simple_action_client.h>
   
   typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
   
   int main(int argc, char** argv){
     ros::init(argc, argv, "simple_navigation_goals");
     bool lr = 1;
     bool rot = 1;
     ros::NodeHandle node; 
     //tell the action client that we want to spin a thread by default
     MoveBaseClient ac("move_base", true);
     tf::TransformListener listener1;
     tf::TransformListener listener2;
     //wait for the action server to come up
     while(!ac.waitForServer(ros::Duration(5.0))){
       ROS_INFO("Waiting for the move_base action server to come up");
     }
   
     move_base_msgs::MoveBaseGoal goal;
   
     ros::Rate rate(10.0);
    while (node.ok()){
    tf::StampedTransform transform;
    try {
    	listener1.waitForTransform("/object_8", "/map", ros::Time(0), ros::Duration(1.0));
    	listener1.lookupTransform("/object_8", "/map", ros::Time(0), transform);
	goal.target_pose.header.frame_id = "base_link";
     break;
  
    ROS_INFO("Robot Found.. Stopping navigation.");
	} catch (tf::TransformException ex) {
   	 ROS_ERROR("%s",ex.what());
     goal.target_pose.header.frame_id = "base_link";
     goal.target_pose.header.stamp = ros::Time::now();
     goal.target_pose.pose.position.x = 0.5;
     goal.target_pose.pose.position.y = 0.0;
     goal.target_pose.pose.position.z = 0.0;
     goal.target_pose.pose.orientation.w = 1.0;
     goal.target_pose.pose.orientation.x = 0.0;
     goal.target_pose.pose.orientation.y = 0.0;
     goal.target_pose.pose.orientation.z = 0.0;
  
    ROS_INFO("Moving Forward");
goal.target_pose.header.stamp = ros::Time::now();
    ac.sendGoal(goal);
  
    ac.waitForResult();

   if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
     ROS_INFO("No obstacle yet");
	if (rot == 1){
		lr = !lr;  
		rot = 0;
 		}     
	}
   else{ 
     
     goal.target_pose.header.frame_id = "base_link";
     
     goal.target_pose.pose.position.x = 0.0;
     goal.target_pose.pose.position.y = 0.0;
     goal.target_pose.pose.position.z = 0.0;
     goal.target_pose.pose.orientation.w = 1.0;
     goal.target_pose.pose.orientation.x = 0.0;
     goal.target_pose.pose.orientation.y = 0.0;
    if ((lr == 1)){
     goal.target_pose.pose.orientation.z = 0.6;
     ROS_INFO("Obstacle ahead.. Turning left");}
    else if ((lr == 0))
     {goal.target_pose.pose.orientation.z = -0.6;
     ROS_INFO("Obstacle ahead.. Turning right");}
    else{}
     rot = 1;
    goal.target_pose.header.stamp = ros::Time::now();
     ac.sendGoal(goal);
    ac.waitForResult();
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("that's fine");}
    else{
    lr = !lr;
    ROS_INFO("There also obstacle");}
}
}
  }





   return 0;
 }



