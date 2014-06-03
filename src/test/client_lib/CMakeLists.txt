cmake_minimum_required(VERSION 2.8)
project( ClientLibTest )
set( name test_client_lib )


include_directories(${ClientLib_SOURCE_DIR})

add_executable(${name}
                    
                    GridCellTest.cpp
                    GridTest.cpp
                    GameManagerTest.cpp
)

target_link_libraries(${name} ${GTEST_LIBS} lib_client)
add_custom_command(TARGET ${name} POST_BUILD COMMAND ${name})
add_test(TEST ${name})

install(TARGETS ${name} DESTINATION test)