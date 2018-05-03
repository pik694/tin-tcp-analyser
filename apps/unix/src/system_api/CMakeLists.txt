
file(GLOB_RECURSE SOURCES "*.cpp")

add_library(system_api ${SOURCES} ../program/Program.cpp ../program/Program.h ../main.cpp ../program/ProgramInitializer.cpp ../program/ProgramInitializer.h)
