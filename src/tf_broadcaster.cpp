# define M_PI           3.14159265358979323846  /* pi */
#include <math.h>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Quaternion.h>
#include <sensor_msgs/Imu.h>



void imuRead(const sensor_msgs::Imu& razor){  //const geometry_msgs::Quaternion& quaternion
   
   static tf::TransformBroadcaster broadcaster;



   broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(razor.orientation.x, razor.orientation.y, razor.orientation.z, razor.orientation.w), tf::Vector3(0.0, 0.0, 0.03)), 
        ros::Time::now(),"world", "base_imu_link"));

   tf::Quaternion q;
   q.setRPY(0, M_PI/2, 0);

   broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(q, tf::Vector3(.05, 0.0, -0.03)), 
        ros::Time::now(),"base_imu_link", "laser"));  //M_PI/2

   /*broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0.0, 0.0, 0.0, 1),tf::Vector3(0.0, 0.0, 0.0)), 
        ros::Time::now(),"laser", "cloud"));  //M_PI/2*/

        //razor.orientation.x
      

   //ROS_INFO(" %f ", razor.orientation.x);
   //ROS_INFO(" test ");
}

/*void scanRead(const sensor_msgs::LaserScan& hok){  //const sensor_msgs::LaserScan& hok
   
   static tf::TransformBroadcaster br;

   br.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0, 0.0, 0.0)), 
        ros::Time::now(),"imu", "laser"));

        //razor.orientation.x
      

   //ROS_INFO(" %f ", razor.orientation.x);
   //ROS_INFO(" test ");
}*/




/*//we'll create a point in the base_laser frame that we'd like to transform to the base_link frame
  geometry_msgs::PointStamped laser_point;
  laser_point.header.frame_id = "base_laser";

  //we'll just use the most recent transform available for our simple example
  laser_point.header.stamp = ros::Time();

  //just an arbitrary point in space
  laser_point.point.x = 1.0;
  laser_point.point.y = 0.2;
  laser_point.point.z = 0.0;

  try{
    geometry_msgs::PointStamped base_point;
    listener.transformPoint("base_link", laser_point, base_point);

    ROS_INFO("base_laser: (%.2f, %.2f. %.2f) -----> base_link: (%.2f, %.2f, %.2f) at time %.2f",
        laser_point.point.x, laser_point.point.y, laser_point.point.z,
        base_point.point.x, base_point.point.y, base_point.point.z, base_point.header.stamp.toSec());
  }
  catch(tf::TransformException& ex){
    ROS_ERROR("Received an exception trying to transform a point from \"base_laser\" to \"base_link\": %s", ex.what());
  }
}*/




int main(int argc, char** argv){

  ros::init(argc, argv, "robot_tf_publisher");
  ros::NodeHandle n;

  //ros::Rate r(100);

  tf::TransformBroadcaster broadcaster;

  ros::Subscriber sub = n.subscribe("imu", 1000, &imuRead);

  //ros::Subscriber laz = n.subscribe("scan", 1000, &scanRead);
  
  ros::spin();

  return 0;
}

 /* tf::TransformBroadcaster broadcaster;

  while(n.ok()){
    angle = sin(counter);
    counter = counter + .01;
    if (counter >= 3.14){
	counter = 0.0;
    }
    //ROS_INFO(" %f ", angle);
    ROS_INFO(" %f ", quaternion.x);

    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.5, 0.0, 0.2)),
        ros::Time::now(),"base_link", "laser"));

    r.sleep();
  }
}*/
