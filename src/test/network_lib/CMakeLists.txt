cmake_minimum_required(VERSION 2.8)
project( NetworkLibTest )
set( name test_network )

include_directories(${NetworkLib_SOURCE_DIR})
include_directories(${Message_BINARY_DIR})

add_executable(${name}  
                    MessageHandlerTest.cpp 
                    IoHarbourTest.cpp 
                    ConnectionTest.cpp
                    MessagePackerTest.cpp
                    ConnectionPoolTest.cpp
)

target_link_libraries(${name} ${GTEST_LIBS} network)
add_custom_command(TARGET ${name} POST_BUILD COMMAND ${name})
add_test(TEST ${name})

install(TARGETS ${name} DESTINATION test)