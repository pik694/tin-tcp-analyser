file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(logger_tests ../main_tests.cpp ${SOURCES})
target_link_libraries(logger_tests ${Boost_LIBRARIES} utils)