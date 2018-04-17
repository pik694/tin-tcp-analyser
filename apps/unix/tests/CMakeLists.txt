
enable_testing()

add_executable(unit_tests main_tests.cpp sample_tests/sample_tests.cpp)
target_link_libraries(unit_tests ${Boost_LIBRARIES})

