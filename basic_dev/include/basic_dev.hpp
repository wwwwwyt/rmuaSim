#ifndef _BASIC_DEV_HPP_
#define _BASIC_DEV_HPP_

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include "airsim_ros/VelCmd.h"
#include "airsim_ros/PoseCmd.h"
#include "airsim_ros/Takeoff.h"
#include "airsim_ros/Reset.h"
#include "airsim_ros/Land.h"
#include "airsim_ros/GPSYaw.h"
#include "airsim_ros/CirclePoses.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Pose.h"
#include  "sensor_msgs/Imu.h"
#include <time.h>
#include <stdlib.h>
#include "Eigen/Dense"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"
#include <ros/callback_queue.h>
#include <boost/thread/thread.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include "airsim_ros/AngleRateThrottle.h"
#endif

class BasicDev
{
private:
    cv_bridge::CvImageConstPtr cv_bottom_ptr, cv_front_left_ptr, cv_front_right_ptr;
    cv::Mat front_left_img, front_right_img, bottom_img;

    std::unique_ptr<image_transport::ImageTransport> it;
    ros::CallbackQueue go_queue;
    ros::CallbackQueue front_img_queue;

    // 调用服务前需要定义特定的调用参数
    airsim_ros::Takeoff takeoff;
    airsim_ros::Land land;
    airsim_ros::Reset reset;

    // 使用publisher发布速度指令需要定义 Velcmd , 并赋予相应的值后，将他publish（）出去
    airsim_ros::VelCmd velcmd;

    // 使用publisher发布姿态指令需要定义 Posecmd , 并赋予相应的值后，将他publish（）出去
    airsim_ros::PoseCmd posecmd;

    // 使用publisher发布角速度指令需要定义 AngleRateThrottle , 并赋予相应的值后，将他publish（）出去
    airsim_ros::AngleRateThrottle arthrcmd;

    //无人机信息通过如下命令订阅，当收到消息时自动回调对应的函数
    ros::Subscriber odom_suber;//状态真值
    ros::Subscriber gps_suber;//gps数据
    ros::Subscriber imu_suber;//imu数据
    ros::Subscriber circles_suber;//障碍圈参考位置
    image_transport::Subscriber front_left_view_suber;
    image_transport::Subscriber front_right_view_suber;
    image_transport::Subscriber bottom_view_suber;

    //通过这两个服务可以调用模拟器中的无人机起飞和降落命令
    ros::ServiceClient takeoff_client;
    ros::ServiceClient land_client;
    ros::ServiceClient reset_client;

    //通过这两个publisher实现对无人机的速度控制和姿态控制
    ros::Publisher vel_publisher;
    ros::Publisher pose_publisher;
    ros::Publisher anglerate_publisher;

    void pose_cb(const geometry_msgs::Pose::ConstPtr& msg);
    void gps_cb(const geometry_msgs::Pose::ConstPtr& msg);
    void imu_cb(const sensor_msgs::Imu::ConstPtr& msg);
    void circles_cb(const airsim_ros::CirclePoses::ConstPtr& msg);

    void bottom_view_cb(const sensor_msgs::ImageConstPtr& msg);
    void front_left_view_cb(const sensor_msgs::ImageConstPtr& msg);
    void front_right_view_cb(const sensor_msgs::ImageConstPtr& msg);


public:
    BasicDev(ros::NodeHandle *nh);
    ~BasicDev();

};





