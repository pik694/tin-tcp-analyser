
find_package(Boost 1.66 REQUIRED COMPONENTS unit_test_framework)

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(unit_tests ${SOURCES})
target_link_libraries(unit_tests ${Boost_LIBRARIES} system_api)


add_subdirectory(system_api_tests)