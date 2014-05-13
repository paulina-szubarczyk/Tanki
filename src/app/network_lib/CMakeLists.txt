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
        ${ProtoSources}
)

target_link_libraries(network
        ${Boost_LIBRARIES}
        ${GLOG_LIBRARIES}
        ${PROTOBUF_LIBRARIES}
)

 