file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h*")


add_library(unix-app-lib STATIC ${SOURCES} ${HEADERS})
target_link_libraries(unix-app-lib ${Boost_LIBRARIES})

add_executable(unix-app ${SOURCES} ${HEADERS})
target_link_libraries(unix-app ${Boost_LIBRARIES})