
function(CompileExample name)
    add_executable(${name}  ${name}.cpp )
    target_link_libraries(${name} ros_wrapper)

    if(USING_ROS2)
        install(TARGETS ${name} DESTINATION lib/${PROJECT_NAME})
    endif()

    if(USING_ROS1)
        install(TARGETS ${name} DESTINATION l${CATKIN_PACKAGE_BIN_DESTINATION})
    endif()
)
endfunction()

CompileExample(listener)
CompileExample(talker)







