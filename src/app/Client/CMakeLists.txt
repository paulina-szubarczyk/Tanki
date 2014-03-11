cmake_minimum_required(VERSION 2.8)
project( Client )


add_executable(client main_client.cpp)
#add_executable(client main_client.cpp ClientTcpConnection.cpp)
target_link_libraries( client messages ${CommonLibs} )