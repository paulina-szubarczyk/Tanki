cmake_minimum_required(VERSION 2.8)
project( GameEngineTest )
enable_testing()

include_directories(${GameEngineLib_SOURCE_DIR})

add_executable(test_game_engine
                    ${Test_SOURCE_DIR}/main_test.cpp 
                    SmallGameShipTest.cpp
                    BigGameShipTest.cpp
                    FieldTest.cpp
                    FieldsUpdaterTest.cpp 
                    GameboardTest.cpp
)

target_link_libraries(test_game_engine gtest gtest_main game_engine)

add_test(test_game_engine test_game_engine)
add_custom_command(TARGET test_game_engine POST_BUILD COMMAND test_game_engine)