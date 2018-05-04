file(GLOB_RECURSE SOURCES "*.cpp")

add_library(utils STATIC ${SOURCES} system_api/TCPOptions.h)
