file(GLOB_RECURSE SOURCES "*.cpp")

add_library(runnable_module STATIC ${SOURCES} Runnable.h)
