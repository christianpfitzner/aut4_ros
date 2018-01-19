/*
 * reactive_navigation.cpp
 *
 *  Created on: 20.12.2015
 *      Author: Christian Pfitzner
 */

#include <ros/ros.h>
#include <sensor_msgs/Range.h>
#include <geometry_msgs/Twist.h>


// global variables
sensor_msgs::Range _left;
sensor_msgs::Range _mid;
sensor_msgs::Range _right;

ros::Publisher _twistPub;

/**
 * Callback function for left sonar
 */
void sonarLeftCallback(const sensor_msgs::Range &msg)
{
   _left = msg;
}


/**
 * Callback function fo right sonar sensor
 */
void sonarRightCallback(const sensor_msgs::Range& msg)
{
   _right = msg;
}

/**
 * Callback function for front sonar
 */
void sonarMidCallback(const sensor_msgs::Range& msg)
{
   _mid = msg;
}

void publishTwist(void)
{
   double lDist = 1.0;
   double rDist = 1.0;
   double mDist = 1.0;

   /*
    * This is necessary for simulation
    * Please do not change the following three lines
    */
   if (!isinf(_left.range))   lDist = _left.range;
   if (!isinf(_mid.range))    mDist = _mid.range;
   if (!isinf(_right.range))  rDist = _right.range;

   geometry_msgs::Twist v;

   /*
    * implement here your code for reactive navigation via ultra sonic
    */

   //
   //
   //
   //
   //
   //



   /*
    * limit velocity for a real robot simulation
    */
   const float v_max   = 1.0; // define maximum velocity in x direction
   const float yaw_max = 1.0; // define maximum turn speed in rad

   if(v.linear.x  > v_max )  v.linear.x  =  v_max;
   if(v.linear.x  < -v_max)  v.linear.x  = -v_max;
   if(v.angular.z > yaw_max) v.angular.z =  yaw_max;
   if(v.angular.z < yaw_max) v.angular.z = -yaw_max;

   // publish the velocity commands
   _twistPub.publish(v);

}

int main(int argc, char **argv)
{
   ros::init(argc, argv, "reactive_navigation");

   ros::NodeHandle nh;

   // init publishers
   _twistPub = nh.advertise<geometry_msgs::Twist>("robot0/cmd_vel", 1);

   // init subscribers
   ros::Subscriber rangeLeftSub  = nh.subscribe("robot0/sonar_1", 1, sonarLeftCallback);
   ros::Subscriber rangeRigthSub = nh.subscribe("robot0/sonar_2", 1, sonarRightCallback);
   ros::Subscriber rangeMidSub   = nh.subscribe("robot0/sonar_0", 1, sonarMidCallback);

   ros::Rate l(10);

   while (ros::ok()) {
      publishTwist();
      ros::spinOnce();
      l.sleep();
   }

}
