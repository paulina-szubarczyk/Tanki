cmake_minimum_required(VERSION 2.8)
project( Client )

include_directories(${ServerLib_SOURCE_DIR})

add_executable(client client.cpp)
target_link_libraries( client lib_server messages ${CommonLibs} )