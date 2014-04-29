cmake_minimum_required(VERSION 2.8)
project( Test )

#	Compile and set up google test
add_subdirectory(gmock)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

set(GTEST_LIBS gmock gmock_main)


enable_testing()
add_subdirectory(network_lib)
add_subdirectory(game_engine_lib)
add_subdirectory(client_lib)