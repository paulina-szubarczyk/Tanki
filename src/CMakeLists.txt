cmake_minimum_required(VERSION 2.8)
project( Tanki )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
find_package( Boost 1.55 COMPONENTS system thread chrono date_time REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )
link_directories( ${Boost_LIBRARY_DIRS} )

include_directories( ${CMAKE_SOURCE_DIR} )

add_executable(exe main.cpp)
target_link_libraries( exe ${Boost_LIBRARIES} )
