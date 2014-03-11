

add_executable(client main_client.cpp)
#add_executable(client main_client.cpp ClientTcpConnection.cpp)
target_link_libraries( client messages ${CommonLibs} )