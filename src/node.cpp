#include "ros_wrapper/node.h"

namespace rosw
{

#ifdef USING_ROS2
std::shared_ptr<rclcpp::Node> _global_node_handle;

void init(int argc, char** argv, const std::string& global_node_name)
{
  rclcpp::init(argc, argv);
  _global_node_handle = std::make_shared<rclcpp::Node>(global_node_name);
}

void spin()
{
  rclcpp::spin(_global_node_handle);
}

void spinOnce()
{
  rclcpp::spin_some(_global_node_handle);
}

bool ok()
{
  return rclcpp::ok();
}

#elif USING_ROS1

void init(int argc, char** argv, const std::string& global_node_name)
{
  ros::init(argc, argv, global_node_name);
}

void spin()
{
  ros::spin();
}

void spinOnce()
{
  ros::spinOnce();
}

bool ok()
{
  return ros::ok();
}

#endif

}  // namespace rosw