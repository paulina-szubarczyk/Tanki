cmake_minimum_required(VERSION 2.8)
project( NetworkLib )

include_directories(${Message_BINARY_DIR})

add_library(network
        MessageHandler.cpp 
        IoHarbour.cpp 
        Connection.cpp
        Acceptor.cpp
        BasicAcceptor.cpp
        ProtobufConnection.cpp
        MessagePacker.cpp
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

 