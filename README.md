# TurtleSwarmMapper

3D Exploration from 2 robots, sharing their map when detecting each other

## gazebo_concert_yanik
own simulation for gazebo with 2 turtlebots

> roslaunch gazebo_concert_yanik concert.launch --screen
> rocon_remocon

- Dependencies : gazebot_concert
- Tutorial : http://wiki.ros.org/gazebo_concert

## yanik_concert
own concert

services : 
* Admin
* teleop
* chatter (add "Yanik Concert" to the whitelist of Chatter_concert) 

> rocon_launch yanik_concert start_solution_and_robot.concert --screen
> rocon_remocon

- Dependencies : concert_master
- Tutorial : http://wiki.ros.org/rocon_concert/Tutorials/indigo/Create%20Your%20Own%20Solution

## Multi-robot-simulation
launcher for stage world with 2 robots, mapping and move_base in each of them

> roslaunch multi-robot-simulation master.launch

- Dependencies : stage_ros, gmapping, move_base, adhoc_communication
- Tutorial : http://wiki.ros.org/adhoc_communication
