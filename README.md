# TurtleSwarmMapper

3D Exploration from 2 robots, sharing their map when detecting each other. 

**Scenario** : 2 robots scanning the environment are creating a 2D map and a 3D point cloud from their part.
               They move randomly inside their map avoiding obstacles
               At the same time, they send their 3D maps through adhoc-communication to the workstation
               Each of them have a picture on its back in order to be recognizable by the other
               Once a robot detects this picture on its team-mate, they stop exploring
               The robot shares the estimated other robot position to the workstation
               The workstation transforms the point cloud of the second robot in the reference frame of the first one
               The point clouds are merged and a big 3D map is created
               

## tsm_nav

Main package for navigation, mapping, 3D scanning and Pose estimation
launcher for real turtlebot with rplidar node, gmapping, move_base

     roslaunch tsm_nav bringup_map_move.launch

- Dependencies : rplidar_node, turtlebot_le2i, gmapping, move_base

## tsm_share_maps
launcher for map exchange through adhoc_communication, node for calling adhoc_communication services 

    #in simulation
    rosrun tsm_share_maps change_membership_client /robot_0 /adhoc_communication/ mc_robot_1 1

    #with running rtabmap
    rosrun tsm_share_maps send_pointcloud_client
    rosrun tsm_share_maps send_tf_client

- Dependencies : adhoc_communication, sensor_msgs

## adhoc_communication
already existing package for communication with new services
new srv :
* SendPointCloud

    #for real communication
    rosrun adhoc_communication adhoc_communication

- Tutorial : http://wiki.ros.org/adhoc_communication

## gazebo_concert_yanik
own simulation for gazebo with 2 turtlebots

    roslaunch gazebo_concert_yanik concert.launch --screen
    rocon_remocon

- Dependencies : gazebot_concert
- Tutorial : http://wiki.ros.org/gazebo_concert

## yanik_concert
own concert

services : 
* Admin
* teleop
* chatter (add "Yanik Concert" to the whitelist of Chatter_concert) 

    rocon_launch yanik_concert start_solution_and_robot.concert --screen
    rocon_remocon

- Dependencies : concert_master
- Tutorial : http://wiki.ros.org/rocon_concert/Tutorials/indigo/Create%20Your%20Own%20Solution

## Multi-robot-simulation
launcher for stage world with 2 robots, mapping, move_base and sharing data in each of them

    roslaunch multi-robot-simulation master.launch

    roslaunch multi-robot-simulation call_services.launch

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

- Dependencies : stage_ros, gmapping, move_base, adhoc_communication
- Tutorial : http://wiki.ros.org/adhoc_communication
