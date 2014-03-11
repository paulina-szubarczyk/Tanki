cmake_minimum_required(VERSION 2.8)
project( Tanki )

set(CMAKE_CXX_COMPILER_FLAGS "${CMAKE_CXX_COMPILER_FLAGS} -std=c++11 -Wall")

add_subdirectory(app)
add_subdirectory(test)
  