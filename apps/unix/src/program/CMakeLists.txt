file(GLOB_RECURSE SOURCES "*.cpp")

add_library(program STATIC ${SOURCES} Program.h)
