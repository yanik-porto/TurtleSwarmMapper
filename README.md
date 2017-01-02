# TurtleSwarmMapper

3D Exploration from 2 turtlebots, sharing their map when detecting each other. 

*distro : INDIGO*

**Scenario** : 

- 2 robots scanning the environment are creating a 2D map and a 3D point cloud from their part.
- They move randomly inside their map avoiding obstacles \s \s
- At the same time, they send their 3D maps through adhoc-communication to the workstation
- Each of them have a picture on its back in order to be recognizable by the other
- Once a robot detects this picture on its team-mate, they stop exploring
- The robot shares the estimated other robot position to the workstation
- The workstation transforms the point cloud of the second robot in the reference frame of the first one
- The point clouds are merged and a big 3D map is created

## Preliminary installations

    $ sudo apt-get install ros-indigo-turtlebot-bringup ros-indigo-turtlebot-navigation ros-indigo-rtabmap-ros
    
    $ git clone https://github.com/introlab/find-object.git
    
    $ git clone https://github.com/roboticslab-fr/rplidar-turtlebot2.git
    
    $ git clone -b indigo https://github.com/aau-ros/aau_multi_robot.git


## Launcher

From robots : 
    
    #Bringup robot, Scan, Explore
    roslaunch tsm_nav bringup_map_move.launch

    #Communicate
    roslaunch tsm_share_maps share_cloud_and_tf.launch

From Workstation (in two terminals) : 
    
    #Visualize (Add -> PointCloud2 -> Topic)
    rosrun rviz rviz

# PACKAGES 

## tsm_nav
Main package for navigation, mapping, 3D scanning and Pose estimation. 

- Dependencies : rplidar_node, turtlebot_le2i, rtabmap_ros, move_base, find_object_2d

---
     roslaunch tsm_nav bringup_map_move.launch

Launcher for real turtlebot with : bringup minimal, rplidar node, rtabmap mapping, move_base, navigation goals, find object 2D. The turtlebot will start, open the kinect (and the rplidar if it is plugged). It is then creating a 2D, 3D map, and moving randomly inside. This launch file embeds also the image detection and pose estimation. 

## adhoc_communication
Existing cloned package for communication with new services. It sends data through wifi when the node is launched on different machines and when they are neighbors. 

- Tutorial : http://wiki.ros.org/adhoc_communication

new srv :
* SendPointCloud
* SendTf

---
    #for real communication
    rosrun adhoc_communication adhoc_communication

Running the node without any specification is taking the wifi connected on wlan0 of the computer. If an other machine is running the node with the same wifi, this machine will appear has new neighbor. 

## tsm_share_maps
Launcher for map exchange through adhoc_communication, clients for adhoc_communication services 

- Dependencies : adhoc_communication, sensor_msgs

---
    #with running rtabmap
    roslaunch tsm_share_maps share_cloud_and_tf.launch

Launch adhoc_communication node, a client for send_pointcloud service and a client for send_tf service

Change the name of the laptop you wanna access (dst_robot) inside send_pointcloud_client.cpp and send_tf_client.cpp (do not forget to recompile). The name of the topic published on the other laptop can also be found in these files. 

## my_pcl_tutorial 
Node transforming the pointcloud from one reference frame to the other

- Dependencies : pcl_ros, pcl_conversions

---
    rosrun my_pcl_tutorial example

# TESTS

## Multi-robot-simulation
Launcher for stage world with 2 robots, mapping, move_base and sharing data in each of them. This is for a test of the adhoc_communication on a single machine

- Dependencies : stage_ros, gmapping, move_base, adhoc_communication
- Tutorial : http://wiki.ros.org/adhoc_communication

---
    #Launch stage world, gmapping, move_base and adhoc_communication
    roslaunch multi-robot-simulation master.launch

    #Launch services for changing membership of neighbors
    roslaunch multi-robot-simulation call_services.launch

    #Call a service manually, send a Twist message
    rosservice call /robot_0/adhoc_communication/send_twist "dst_robot: 'robot_1'
    topic: '/cmd_vel'
    twist:
      linear:
    x: 1.0
    y: 0.0
    z: 0.0
      angular:
    x: 0.0
    y: 0.0
    z: 0.0" 

## gazebo_concert_yanik
own simulation for gazebo with 2 turtlebots

- Dependencies : gazebot_concert
- Tutorial : http://wiki.ros.org/gazebo_concert

---
    roslaunch gazebo_concert_yanik concert.launch --screen
    rocon_remocon

## yanik_concert
Own concert. Test for accessing the map of two robots. Some dropped leads on services. 

- Dependencies : concert_master
- Tutorial : http://wiki.ros.org/rocon_concert/Tutorials/indigo/Create%20Your%20Own%20Solution

services : 
* Admin
* teleop
* chatter (add "Yanik Concert" to the whitelist of Chatter_concert) 

---
    rocon_launch yanik_concert start_solution_and_robot.concert --screen
    rocon_remocon
    
# VIDEO

youtube video link : https://www.youtube.com/watch?v=o8uTnPNlolE&feature=youtu.be



