#pragma once

#ifdef USING_ROS2

#include <std_msgs/msg/string.hpp>

namespace rosw::std_msgs
{
  using String = ::std_msgs::msg::String;
  using String_ConstPtr = std::shared_ptr<::std_msgs::msg::String const>;
}

#elif USING_ROS1

#include <std_msgs/String.h>

namespace rosw::std_msgs
{
  using String = ::std_msgs::String;
  using String_ConstPtr = boost::shared_ptr<const ::std_msgs::String>;
}

#endif