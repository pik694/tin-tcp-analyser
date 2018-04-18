enable_testing()

find_package(Boost 1.60.0 REQUIRED COMPONENTS unit_test_framework)

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(unit_tests ${SOURCES})
target_link_libraries(unit_tests ${Boost_LIBRARIES} unix-app-lib)