cmake_minimum_required(VERSION 2.8)
project( App )

#	CMake module path for custom module finding
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMakeScripts)

#	Include directories for easier handling of includes
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_BINARY_DIR}/app )

#	Boost
find_package( Boost 1.55 COMPONENTS system  thread chrono date_time REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )
link_directories( ${Boost_LIBRARY_DIRS} )

#	Google Protocol Buffers
find_package( Protobuf REQUIRED )
include_directories(${PROTOBUF_INCLUDE_DIR})
file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${ProtoFiles})

#	Google-glog
find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS})

add_subdirectory(network_lib)
add_subdirectory(client_lib)
add_subdirectory(game_engine_lib)
add_subdirectory(execs)
