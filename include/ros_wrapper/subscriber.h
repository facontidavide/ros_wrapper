#pragma once


#ifdef USING_ROS2
#include <rclcpp/rclcpp.hpp>
#endif

#ifdef USING_ROS1
#include <ros/ros.h>
#endif


namespace rosw
{

#ifdef USING_ROS2

using Subscriber = std::shared_ptr<rclcpp::SubscriptionBase>;
extern std::shared_ptr<rclcpp::Node> _global_node_handle;

#elif USING_ROS1

using Subscriber = ros::Subscriber;

#endif

} // end namespace rosw
