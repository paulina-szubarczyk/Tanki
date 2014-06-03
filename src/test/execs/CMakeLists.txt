cmake_minimum_required(VERSION 2.8)
project( ExecsTest )
set( name test_execs )

include_directories(${GameEngineLib_SOURCE_DIR})
include_directories(${Message_BINARY_DIR})
include_directories(${NetworkLib_SOURCE_DIR})
include_directories(${Execs_SOURCE_DIR})
include_directories(${ClientLib_SOURCE_DIR})

add_executable(${name}
        ConnectionBridgeTest.cpp
        PlayerOutputTest.cpp
)

target_link_libraries(${name} ${GTEST_LIBS} exec)
add_custom_command(TARGET ${name} POST_BUILD COMMAND ${name})
add_test(TEST ${name})

install(TARGETS ${name} DESTINATION test)