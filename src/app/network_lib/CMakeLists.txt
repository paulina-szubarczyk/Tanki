cmake_minimum_required(VERSION 2.8)
project( NetworkLib )

add_library(network
        MessageHandler.cpp 
        IoHarbour.cpp 
        Connection.cpp
        Acceptor.cpp
        BasicAcceptor.cpp
        ProtobufConnection.cpp
        MessagePacker.cpp
        )
        
target_link_libraries(network ${CommonLibs})

 