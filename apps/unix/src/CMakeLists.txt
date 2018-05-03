add_subdirectory(program)

add_executable(analyser main.cpp)
target_link_libraries(analyser program)

