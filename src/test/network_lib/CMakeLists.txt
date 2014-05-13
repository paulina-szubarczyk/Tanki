cmake_minimum_required(VERSION 2.8)
project( NetworkTest )
enable_testing()

include_directories(${NetworkLib_SOURCE_DIR})

add_executable(test_network
                    ${Test_SOURCE_DIR}/main_test.cpp 
                    MessageHandlerTest.cpp 
                    IoHarbourTest.cpp 
                    ConnectionTest.cpp
                    MessagePackerTest.cpp
)


target_link_libraries(test_network gtest gtest_main network)

add_test(test_network test_network)
add_custom_command(TARGET test_network POST_BUILD COMMAND test_network)