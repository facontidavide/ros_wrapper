#pragma once


#ifdef USING_ROS2
#include <rclcpp/rclcpp.hpp>
#endif

#ifdef USING_ROS1
#include <ros/ros.h>
#endif

namespace rosw
{

class Publisher
{
public:
  virtual ~Publisher() = default;

  template <typename MsgType>
  void publish(const MsgType& msg);

  protected:
  friend class NodeHandle;

#ifdef USING_ROS2
    rclcpp::PublisherBase::SharedPtr _pub_impl;
#endif

#ifdef USING_ROS1
    ros::Publisher _pub_impl;
#endif
};


//-----------------------------------------------------------
template <typename MsgType> inline
void rosw::Publisher::publish(const MsgType& msg)
{
#ifdef USING_ROS2
  auto impl = dynamic_cast<rclcpp::Publisher<MsgType>*>(_pub_impl.get());
  impl->publish(msg);
#elif USING_ROS1
  _pub_impl.publish(msg);
#endif
}

} // end namespace rosw
