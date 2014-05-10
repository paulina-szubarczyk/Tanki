cmake_minimum_required(VERSION 2.8)
project( Client )

include_directories(${ClientLib_SOURCE_DIR})

add_executable(client main_client.cpp)
#add_executable(client main_client.cpp ClientTcpConnection.cpp)
target_link_libraries( client lib_client messages ${CommonLibs} )