cmake_minimum_required(VERSION 2.8)
project( NetworkLib )

include_directories(
        ${Message_BINARY_DIR}
)

add_library(network
        Acceptor.cpp
        Connection.cpp
        ConnectionPool.cpp
        IoHarbour.cpp 
        MessageHandler.cpp 
        MessageHandlerPolicies.cpp
        MessagePacker.cpp
        PoolingAcceptor.cpp
        ProtobufConnection.cpp
        ProtobufConnectionFactory.cpp   
)
        
target_link_libraries(network 
        ${GLOG_LIBRARIES}
        ${Boost_LIBRARIES}
        message
)

install(TARGETS network
               RUNTIME DESTINATION bin
               LIBRARY DESTINATION lib
               ARCHIVE DESTINATION lib/static
)

 