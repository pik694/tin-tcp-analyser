add_subdirectory(runnable)
add_subdirectory(utils)

add_executable(analyser main.cpp)
target_link_libraries(analyser runnable_module utils ${Boost_LIBRARIES})

