cmake_minimum_required(VERSION 2.8)
project( Test )

#	Compile and set up google test
add_subdirectory(gtest)
#enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(MAIN ${CMAKE_CURRENT_SOURCE_DIR}/main_test.cpp)

add_subdirectory(network_lib)
add_subdirectory(game_engine_lib)
add_subdirectory(client_lib)
