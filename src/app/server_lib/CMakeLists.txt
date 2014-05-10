cmake_minimum_required(VERSION 2.8)
project( ServerLib )

add_library(lib_server session.cpp tcpserver.cpp Player.cpp)

 