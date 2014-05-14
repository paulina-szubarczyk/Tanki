cmake_minimum_required(VERSION 2.8)
project( GameEngineLibTest )
set( name test_game_engine )

include_directories(${GameEngineLib_SOURCE_DIR})

add_executable(${name}
                    ${MAIN} 
                    BigGameShipTest.cpp 
                    FieldsUpdaterTest.cpp 
                    FieldTest.cpp 
                    GameboardTest.cpp 
                    SmallGameShipTest.cpp
)

target_link_libraries(${name} gtest gtest_main game_engine)
add_custom_command(TARGET ${name} POST_BUILD COMMAND ${name})