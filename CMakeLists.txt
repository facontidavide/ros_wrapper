cmake_minimum_required(VERSION 3.8)
project(ros_wrapper)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

<<<<<<< HEAD
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
=======
# find dependencies
find_package(ament_cmake QUIET)
find_package(spdlog REQUIRED)

if ( ament_cmake_FOUND )

  add_definitions( -DUSING_ROS2 )
  message(STATUS "------------------------------------------")
  message(STATUS "Building using COLCON.")
  message(STATUS "------------------------------------------")

  find_package(rclcpp REQUIRED)
  find_package(rcl_interfaces REQUIRED)
  find_package(spdlog_vendor REQUIRED)

  add_library(${PROJECT_NAME} src/ros2_sink.cpp)

  target_link_libraries(${PROJECT_NAME}
    spdlog::spdlog
  )
  ament_target_dependencies(${PROJECT_NAME}
    spdlog_vendor
    rclcpp
    rcl_interfaces
  )

  target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )

  add_executable(example_ros2 src/example_ros2.cpp)
  target_link_libraries(example_ros2 ${PROJECT_NAME})
  target_include_directories(example_ros2 PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )

  install(TARGETS
  ${PROJECT_NAME}
  example_ros2
  DESTINATION lib/${PROJECT_NAME}
)

else()
  add_definitions( -DUSING_ROS )
  message(STATUS "------------------------------------------")
  message(STATUS "Building using CATKIN.")
  message(STATUS "------------------------------------------")

  find_package(catkin REQUIRED COMPONENTS roscpp)
>>>>>>> abaa4efac1adf2df7fb26df68df5c33fc2eedf33

  catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS roscpp
    DEPENDS )

<<<<<<< HEAD
    # TODO
endif()

add_subdirectory(examples)
=======
  include_directories(${catkin_INCLUDE_DIRS})

  add_library(${PROJECT_NAME} src/ros_sink.cpp)
  
  target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )

  target_link_libraries(${PROJECT_NAME}
    spdlog::spdlog
    ${catkin_LIBRARIES}
  )

  add_executable(example_ros src/example_ros.cpp)
  target_link_libraries(example_ros ${PROJECT_NAME} ${catkin_LIBRARIES})
  target_include_directories(example_ros PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )

  install(DIRECTORY include/${PROJECT_NAME}/
          DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION} )

  install(TARGETS ${PROJECT_NAME} example_ros
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
  )
endif()


>>>>>>> abaa4efac1adf2df7fb26df68df5c33fc2eedf33



