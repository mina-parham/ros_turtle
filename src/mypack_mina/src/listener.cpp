#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include <sstream>

turtlesim::Pose position1;
turtlesim::Pose position2;
void LocationOfTurtle1(const turtlesim::Pose::ConstPtr& msg)
{
  
//at first I find the position of  first turtle and print it to make sure that it works correctly!!
 ROS_INFO("i heard:[%f],[%f],[%f],[%f],[%f]\n",msg->x,msg->y,msg->theta,msg->linear_velocity,msg->angular_velocity);

//now I save this number for using it!
position1.x=msg->x;
position1.y=msg->y;
position1.theta=msg->theta;
position1.linear_velocity=msg->linear_velocity;
position1.angular_velocity=msg->angular_velocity;
}
//then I need the location of tutrtle2
void LocationOfTurtle2(const turtlesim::Pose::ConstPtr& msg)
{
  

 ROS_INFO("i heard:[%f],[%f],[%f],[%f],[%f]\n",msg->x,msg->y,msg->theta,msg->linear_velocity,msg->angular_velocity);

//now I save this number then I can pass it to the second turtle!!
position2.x=msg->x;
position2.y=msg->y;
position2.theta=msg->theta;
position2.linear_velocity=msg->linear_velocity;
position2.angular_velocity=msg->angular_velocity;
}
//now I will calculate the distance between two turtles!
double distance(double tur1x,double tur1y,double tur2x,double tur2y){

return sqrt(pow((tur2x-tur1x),2)+pow((tur2y-tur1y),2));
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

 
  ros::NodeHandle n;

 
  ros::Subscriber sub1 = n.subscribe("turtle1/pose", 1000, LocationOfTurtle1);
  ros::Subscriber sub2 = n.subscribe("turtle2/pose", 1000, LocationOfTurtle2);

  ros::init(argc, argv,"talker");
  ros::Publisher pub =n.advertise<geometry_msgs::Twist>("turtle2/cmd_vel",1000);
  ros::Rate loop_rate(10);
  int count=0;
while (ros::ok()){
geometry_msgs::Twist pos;
pos.linear.x=1.5*distance(position2.x,position2.y,position1.x,position2.y);
pos.linear.y=0;
pos.linear.z=0;
pos.angular.x=0;
pos.angular.y=0;
pos.angular.z=4*(atan2(position1.y-position2.y,position1.x-position2.y)-position2.theta);


pub.publish(pos);
ros::spinOnce();
loop_rate.sleep();
++count;
}

  ros::spin();

  return 0;
}
