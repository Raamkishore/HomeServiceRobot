#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"

float pick[3] = {-2.9, 1.90, 1.0};
float drop[3] = {-2.9, -0.06, 1.0};
float thresh[2] = {0.4, 0.3};

bool picked = false;
bool dropped = false;



void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{ 

if (std::abs(pick[0] -msg->pose.pose.position.x) <= thresh[0] && std::abs(pick[1] -msg->pose.pose.position.y) <= thresh[0] && std::abs(pick[2] -msg->pose.pose.orientation.w) <= thresh[1])
   { 
    if(!picked)
    {
     picked = true;
    }
}

if (std::abs(drop[0] -msg->pose.pose.position.x) <= thresh[0] && std::abs(drop[1] -msg->pose.pose.position.y) <= thresh[0] && std::abs(drop[2] -msg->pose.pose.orientation.w) <= thresh[1])
  { 
    if(!dropped)
    {
     dropped = true;
    }
}
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("odom", 1000, OdomCallback);
  


  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = -2.66;
    marker.pose.position.y = 1.90;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.25;
    marker.scale.y = 0.25;
    marker.scale.z = 0.25;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    
   marker_pub.publish(marker);
   ROS_INFO("You can see the pickup point in rviz");
   
   while(!picked)
   {
    ros::spinOnce();
   }
   
   if(picked)
   {
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Picked");
   }  
   
   while(!dropped)
   {
    ros::spinOnce();
   }

   if(dropped)
   {
    marker.pose.position.x = -2.48;
    marker.pose.position.y = -0.06;
    marker.pose.orientation.w = 1.0;
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("Dropped off");
    ros::Duration(5.0).sleep();
   }  
    return 0;
  }
 
}