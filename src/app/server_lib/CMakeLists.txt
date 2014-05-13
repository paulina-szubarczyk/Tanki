cmake_minimum_required(VERSION 2.8)
project( ServerLib )

add_library(lib_server 
        MessageHandler.cpp 
        IoHarbour.cpp 
        Connection.cpp
        Acceptor.cpp
        BasicAcceptor.cpp
        ProtobufConnection.cpp
        )
        
target_link_libraries(lib_server ${CommonLibs})

 