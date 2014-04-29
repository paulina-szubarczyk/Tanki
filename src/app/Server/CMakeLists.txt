cmake_minimum_required(VERSION 2.8)
project( Server )

add_executable(server main_server.cpp session.cpp tcpserver.cpp ship.cpp)
target_link_libraries( server ${CommonLibs} GL GLU glut)
 
