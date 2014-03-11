cmake_minimum_required(VERSION 2.8)
project( Tanki )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall ")

#	CMake module path for custom module finding
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMakeScripts)

#	Include directories for easier handling of includes
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_BINARY_DIR}/app )

#	Boost
find_package( Boost 1.55 COMPONENTS system thread chrono date_time REQUIRED)
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
set(CommonLibs ${CommonLibs} ${GLOG_LIBRARIES})

#	Build a message library
add_library(messages ${ProtoSources} ${ProtoHeaders} packedmessage.h)
target_link_libraries(messages ${PROTOBUF_LIBRARIES})

#	Setup common libraries
set(CommonLibs ${CommonLibs} ${Boost_LIBRARIES} messages)


add_subdirectory(Client)
add_subdirectory(Server)
