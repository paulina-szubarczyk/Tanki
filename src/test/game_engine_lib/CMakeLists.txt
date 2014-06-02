cmake_minimum_required(VERSION 2.8)
project( GameEngineLibTest )
set( name test_game_engine )

include_directories(${GameEngineLib_SOURCE_DIR})
include_directories(${Message_BINARY_DIR})
include_directories(${NetworkLib_SOURCE_DIR})

add_executable(${name}
        BigGameShipTest.cpp
        FieldTest.cpp 
        FieldsUpdaterTest.cpp 
        GameTest.cpp
        GameboardTest.cpp   
        GameEngineTest.cpp     
        GamePlayerTest.cpp
        GamePlayerBuilderTest.cpp
        ShipFactoryMethodTest.cpp
        SmallGameShipTest.cpp 
        PyGameConfigTest.cpp
)

target_link_libraries(${name} ${GTEST_LIBS} game_engine network)
add_custom_command(TARGET ${name} POST_BUILD COMMAND ${name})
add_test(TEST ${name})

install(TARGETS ${name} DESTINATION test)