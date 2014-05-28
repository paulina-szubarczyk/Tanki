cmake_minimum_required(VERSION 2.8)
project( App )

#	Include directories for easier handling of includes
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

#	Boost
find_package( Boost 1.53 COMPONENTS system thread chrono date_time REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )
link_directories( ${Boost_LIBRARY_DIRS} )

#	Google-glog
find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS})

add_subdirectory(proto)
add_subdirectory(client_lib)
add_subdirectory(network_lib)
add_subdirectory(game_engine_lib)
add_subdirectory(execs)
