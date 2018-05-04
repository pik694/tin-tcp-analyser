file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(system_api_tests ../main_tests.cpp ${SOURCES})
target_link_libraries(system_api_tests ${Boost_LIBRARIES} )