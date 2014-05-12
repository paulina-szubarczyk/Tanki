cmake_minimum_required(VERSION 2.8)
project( ServerLibTest )
enable_testing()
include_directories(${ServerLib_SOURCE_DIR})

add_executable(server_lib_test 
                    ${Test_SOURCE_DIR}/main_test.cpp 
                    MessageHandlerTest.cpp 
                    IoHarbourTest.cpp 
                    ConnectionTest.cpp
)


target_link_libraries(server_lib_test gtest gtest_main lib_server)
add_test(server_lib_test server_lib_test)
add_custom_command(TARGET server_lib_test POST_BUILD COMMAND server_lib_test)