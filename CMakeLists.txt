cmake_minimum_required(VERSION 3.8)
project(ros_wrapper)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# set c++ 17
set(CMAKE_CXX_STANDARD 17)

# find ROS version automatically
find_package(ament_cmake QUIET)
find_package(catkin QUIET)

if ( ament_cmake_FOUND )
  set(USING_ROS2 ON) 
  message(STATUS "------------------------------------------")
  message(STATUS "Building using COLCON/AMENT.")
  message(STATUS "------------------------------------------")
elseif(catkin_FOUND)
  set(USING_ROS1 ON)
  message(STATUS "------------------------------------------")
  message(STATUS "Building using CATKIN.")
  message(STATUS "------------------------------------------")
else()
  message(FATAL_ERROR "Can't determine ROS version")
endif()


if(USING_ROS2)
  find_package(rclcpp REQUIRED)
  find_package(spdlog_ros REQUIRED)
  find_package(std_msgs REQUIRED)
  find_package(geometry_msgs REQUIRED)

  add_library(${PROJECT_NAME} src/node.cpp)
  ament_target_dependencies(${PROJECT_NAME} rclcpp spdlog_ros std_msgs geometry_msgs)

  target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
  target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSING_ROS2)

  target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )

  ament_export_dependencies(spdlog_ros rclcpp std_msgs geometry_msgs)
  ament_package()

elseif(USING_ROS1)
  find_package(catkin REQUIRED COMPONENTS roscpp spdlog_ros std_msgs geometry_msgs)
  find_package(spdlog REQUIRED)

  catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS roscpp spdlog_ros
    DEPENDS )

  add_library(${PROJECT_NAME} src/node.cpp)

  target_link_libraries(${PROJECT_NAME} ${catkin_} spdlog::spdlog ${catkin_LIBRARIES})
  target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSING_ROS1)

  target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE: ${catkin_INCLUDE_DIRS}>
  $<INSTALL_INTERFACE:include>
)
endif()

add_subdirectory(examples)




