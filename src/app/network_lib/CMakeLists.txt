cmake_minimum_required(VERSION 2.8)
project( NetworkLib )


find_package(PythonLibs)

include_directories(
        ${Message_BINARY_DIR}
        ${PYTHON_INCLUDE_DIRS}
)

add_library(network
        Acceptor.cpp
        Connection.cpp
        ConnectionFactory.cpp
        ConnectionPool.cpp
        IoHarbour.cpp 
        MessageHandler.cpp 
        MessageHandlerPolicies.cpp
        MessagePacker.cpp
        MessageSender.cpp
        PoolingAcceptor.cpp
        ProtobufConnection.cpp
        ProtobufConnectionFactory.cpp   
        PythonInterpreter.cpp 
)
        
target_link_libraries(network 
        ${GLOG_LIBRARIES}
        ${Boost_LIBRARIES}
        message
        ${PYTHON_LIBRARIES}
)

install(TARGETS network
               RUNTIME DESTINATION bin
               LIBRARY DESTINATION lib
               ARCHIVE DESTINATION lib/static
)

 