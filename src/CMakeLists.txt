cmake_minimum_required(VERSION 2.8)
project( Tanki )

#    Set CMake Install Path
set (CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR} CACHE PATH "default install path" FORCE )

set(CMAKE_CXX_COMPILER_FLAGS ${CMAKE_CXX_COMPILER_FLAGS} -std=c++11 -Wall)

#	CMake module path for custom module finding
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMakeScripts)

add_subdirectory(app)
add_subdirectory(test)