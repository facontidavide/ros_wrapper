#pragma once

#include <any>
#include <string>
#include <functional>
#include <memory>

#include "ros_wrapper/publisher.h"
#include "ros_wrapper/subscriber.h"

namespace rosw
{

void init(int argc, char** argv, const std::string& global_node_name = {});

void spin();

void spinOnce();

bool ok();


class NodeHandle
{
public:
  NodeHandle()
  {
#ifdef USING_ROS2
    _node_impl = _global_node_handle;
#elif USING_ROS1
    _node_impl = ros::NodeHandle();
#endif
  }
 
#ifdef USING_ROS2 
  template <typename MsgType>
  rosw::Subscriber subscribe(const std::string& topic, uint32_t queue_size,
                             std::function<void(const std::shared_ptr<MsgType const>)> callback)
  {
    return _node_impl->create_subscription<MsgType>(topic, queue_size, callback);
  }
#elif USING_ROS1
  template <typename MsgType>
  rosw::Subscriber subscribe(const std::string& topic, uint32_t queue_size,
                             boost::function<void(const boost::shared_ptr<const MsgType>)> callback)
  {
    return _node_impl.subscribe<MsgType>(topic, queue_size, callback);
  }
#endif
  template <typename MsgType>
  rosw::Publisher advertise(const std::string& topic, uint32_t queue_size);

private:

#ifdef USING_ROS2
    std::shared_ptr<rclcpp::Node> _node_impl;
#elif USING_ROS1
    ros::NodeHandle _node_impl;
#endif

};
//-----------------------------------------------------------
#ifdef USING_ROS2

template <typename MsgType> inline
Publisher NodeHandle::advertise(const std::string& topic, uint32_t queue_size)
{
  Publisher out;
  out._pub_impl = _node_impl->create_publisher<MsgType>(topic, queue_size);
  return out;
}
#endif
//-----------------------------------------------------------

#ifdef USING_ROS1

template <typename MsgType> inline
Publisher NodeHandle::advertise(const std::string& topic, uint32_t queue_size)
{
  Publisher out;
  out._pub_impl = _node_impl.advertise<MsgType>(topic, queue_size);
  return out;
}
#endif

}  // namespace rosw