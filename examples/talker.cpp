

#include "ros_wrapper/ros.h"
#include "ros_wrapper/msgs/std_msgs.h"

#include <spdlog/spdlog.h>
#include <chrono>
#include <thread>

int main(int argc, char **argv)
{
  rosw::init(argc, argv, "talker");

  rosw::NodeHandle nh;

  rosw::Publisher chatter_pub = nh.advertise<rosw::std_msgs::String>("chatter", 1000);

  // rosw::Rate loop_rate(10);

  int count = 0;
  while (rosw::ok())
  {
    rosw::std_msgs::String msg;
    msg.data = "hello world " + std::to_string(count);

    spdlog::info("{}", msg.data);

    chatter_pub.publish(msg);
    rosw::spinOnce();

    // loop_rate.sleep();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ++count;
  }


  return 0;
}
