file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(unit_tests ${SOURCES})
target_link_libraries(unit_tests ${Boost_LIBRARIES} system_api runnable_module)


add_subdirectory(system_api_tests)
add_subdirectory(runnable_tests)