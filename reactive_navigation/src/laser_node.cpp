/*
 * braitenberg_node.cpp
 *
 *  Created on: 20.12.2015
 *      Author: chris
 */

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

sensor_msgs::LaserScan _scan;
ros::Publisher         _twistPub;

const double _phi_threshold   = 1.0;
const double _range_threshold = 2.0;

/**
 * Function to check if angle is in direciton of driving
 */
int isAngleInDrivingDirection(const double& phi)
{
   if (fabs(phi) < _phi_threshold) return 1;
   else                            return 0;
}


/**
 * Function to check if distance is greater than threshold
 */
int isDistanceGreat(const double& range)
{
   if (range > _range_threshold) return 1;
   else                          return 0;
}


/**
 * Function to publish velocity
 */
void publishTwist(void)
{

   // please implement a reactive laser behaviour in the following lines
   double alpha = 0.0;  // speed for yaw angle
   double speed = 0.0;  // speed in x direction












   geometry_msgs::Twist v;

 
  /**
   * bug fix for simulation:
   * Values close to zero cause problems in the simulation.
   * Below a given threshold the velocity is set to zero to
   * solve this problem.
   */
   v.linear.x = speed;
   if (speed < 0.01)       alpha = 0.5;
   if (fabs(alpha) < 0.05) alpha = 0.0;
   v.angular.z = alpha;

   _.twistPub

   // limit velocity for simulation

   const float v_max   = 1.0; // define maximum velocity in x direction
   const float yaw_max = 1.0; // define maximum turn speed in rad

   if(v.linear.x  > v_max )   v.linear.x  =  v_max;
   if(v.linear.x  < -v_max)   v.linear.x  = -v_max;
   if(v.angular.z > yaw_max)  v.angular.z =  yaw_max;
   if(v.angular.z < -yaw_max) v.angular.z = -yaw_max;

   _twistPub.publish(v);

   // broadcast velocity
   _twistPub.publish(v);
}

/**
 * Callback function for laser
 */
void laserCallback(const sensor_msgs::LaserScan &msg)
{
   _scan = msg;
   publishTwist();
}

int main(int argc, char **argv)
{
   ros::init(argc, argv, "reactive_laser");

   ros::NodeHandle nh;

   _twistPub = nh.advertise < geometry_msgs::Twist > ("robot0/cmd_vel", 1);



   ros::Subscriber rangeLeftSub = nh.subscribe("robot0/laser_0", 1, laserCallback);

   ros::spin();

}
