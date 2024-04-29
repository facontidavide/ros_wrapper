
function(CompileExample name)
    add_executable(${name}  ${name}.cpp )
    target_link_libraries(${name} ros_wrapper)

    install(TARGETS ${name}
    DESTINATION lib/${PROJECT_NAME})
endfunction()

CompileExample(listener)
CompileExample(talker)







