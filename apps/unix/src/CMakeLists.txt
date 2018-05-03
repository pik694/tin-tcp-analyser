add_subdirectory(runnable)

add_executable(analyser main.cpp ./program/Program.cpp ./program/ProgramInitializer.cpp)
target_link_libraries(analyser ${Boost_LIBRARIES})

