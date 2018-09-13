#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include <sstream>

turtlesim::Pose position;
void LocationOfTurtle(const turtlesim::Pose::ConstPtr& msg)
{
  
//at first I find the position of  first turtle and print it to make sure that it works correctly!!
 ROS_INFO("i heard:[%f],[%f],[%f],[%f],[%f]\n",msg->x,msg->y,msg->theta,msg->linear_velocity,msg->angular_velocity);

//now I save this number then I can pass it to the second turtle!!
position.x=msg->x;
position.y=msg->y;
position.theta=msg->theta;
position.linear_velocity=msg->linear_velocity;
position.angular_velocity=msg->angular_velocity;
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

 
  ros::NodeHandle n;

 
  ros::Subscriber sub = n.subscribe("turtle1/pose", 1000, LocationOfTurtle);

  ros::init(argc, argv,"talker");
  ros::Publisher pub =n.advertise<geometry_msgs::Twist>("turtle2/cmd_vel",1000);
  ros::Rate loop_rate(10);
  int count=0;
while (ros::ok()){
geometry_msgs::Twist pos;
pos.linear.x=0;
pos.linear.y=0;
pos.linear.z=0;
pos.angular.x=0;
pos.angular.y=0;
pos.angular.z=0;
pub.publish(pos);
ros::spinOnce();
loop_rate.sleep();
++count;
}

  ros::spin();

  return 0;
}
