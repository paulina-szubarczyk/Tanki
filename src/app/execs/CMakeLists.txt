cmake_minimum_required(VERSION 2.8)
project( Execs )

include_directories(${Message_BINARY_DIR})
include_directories(${NetworkLib_SOURCE_DIR})

add_executable(server server.cpp)        
target_link_libraries(server network )

add_executable(client client.cpp)
target_link_libraries( client network )

install(TARGETS client server
               RUNTIME DESTINATION bin
               LIBRARY DESTINATION lib
               ARCHIVE DESTINATION lib/static
)
