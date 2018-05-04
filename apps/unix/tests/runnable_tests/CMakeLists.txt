file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(runnable_tests ../main_tests.cpp ${SOURCES})
target_link_libraries(runnable_tests ${Boost_LIBRARIES} runnable_module utils)