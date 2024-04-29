#pragma once

#ifdef USING_ROS2

#include <std_msgs/msg/string.hpp>

namespace rosw::std_msgs
{
  using String = ::std_msgs::msg::String;

}

#elif USING_ROS1



#endif