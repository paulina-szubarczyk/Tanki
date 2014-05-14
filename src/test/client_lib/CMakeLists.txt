cmake_minimum_required(VERSION 2.8)
project( ClientLibTest )
set( name test_client_lib )

include_directories(${ClientLib_SOURCE_DIR})

add_executable(${name} 
                    ${MAIN} 
                    shiptest.cpp
)

target_link_libraries(${name} gtest gtest_main lib_client)
add_custom_command(TARGET ${name} POST_BUILD COMMAND ${name})