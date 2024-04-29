
#include "ros_wrapper/ros.h"
#include "spdlog/spdlog.h"
#include "ros_wrapper/msgs/std_msgs.h"

void chatterCallback(const std::shared_ptr<rosw::std_msgs::String> msg)
{
  spdlog::info("I heard: [{}]", msg->data);
}


int main(int argc, char **argv)
{
  rosw::init(argc, argv, "listener");

  rosw::NodeHandle nh;

  rosw::Subscriber sub = nh.subscribe<rosw::std_msgs::String>("chatter", 100, chatterCallback);

  rosw::spin();

  return 0;
}
