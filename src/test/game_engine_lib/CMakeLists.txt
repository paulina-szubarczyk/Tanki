cmake_minimum_required(VERSION 2.8)
project( GameEngineLibTest )
set( name test_game_engine )

include_directories(${GameEngineLib_SOURCE_DIR})

add_executable(${name}
                    BigGameShipTest.cpp 
                    FieldsUpdaterTest.cpp 
                    FieldTest.cpp 
                    GameboardTest.cpp 
                    SmallGameShipTest.cpp
)

target_link_libraries(${name} ${GTEST_LIBS} game_engine)
add_custom_command(TARGET ${name} POST_BUILD COMMAND ${name})
add_test(TEST ${name})

install(TARGETS ${name} DESTINATION test)