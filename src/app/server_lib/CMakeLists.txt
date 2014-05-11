cmake_minimum_required(VERSION 2.8)
project( ServerLib )

add_library(lib_server session.cpp tcpserver.cpp MessageHandler.cpp IoHarbour.cpp)
target_link_libraries(lib_server ${CommonLibs})

 