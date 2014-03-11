




add_executable(server main_server.cpp session.cpp tcpserver.cpp)
target_link_libraries( server ${CommonLibs})
