#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include <sstream>


void chatterCallback(const turtlesim::Pose::ConstPtr& msg)
{
  

 ROS_INFO("i heard:[%f],[%f],[%f],[%f],[%f]\n",msg->x,msg->y,msg->theta,msg->linear_velocity,msg->angular_velocity);
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
ros::init(argc, argv,"talker");
 
  ros::NodeHandle n;

 
  ros::Subscriber sub = n.subscribe("turtle1/pose", 1000, chatterCallback);

 
  ros::spin();

  return 0;
}
