# TurtleSwarmMapper

3D Exploration from 2 robots, sharing their map when detecting each other

## gazebo_concert_yanik
own simulation for gazebo with 2 turtlebots

> roslaunch gazebo_concert_yanik concert.launch --screen
> rocon_remocon

## yanik_concert
own concert

services : 
* Admin
* teleop
* chatter (add "Yanik Concert" to the whitelist of Chatter_concert) 

> rocon_launch yanik_concert start_solution_and_robot.concert --screen
> rocon_remocon

## Multi-robot-simulation
launcher for stage world with 2 robots, mapping and move_base in each of them

> roslaunch multi-robot-simulation master.launch
