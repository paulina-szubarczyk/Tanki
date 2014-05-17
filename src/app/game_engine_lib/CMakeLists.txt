cmake_minimum_required(VERSION 2.8)
project( GameEngineLib )

include_directories(${Message_BINARY_DIR})
include_directories(${NetworkLib_SOURCE_DIR})

add_library(game_engine 
        Field.cpp 
        GameShip.cpp 
        SmallGameShip.cpp 
        BigGameShip.cpp 
        HitObserver.cpp
        FieldsUpdater.cpp 
        ShipObserver.cpp 
        Gameboard.cpp
        ShipFactoryMethod.cpp
        GamePlayer.cpp
        PlayerBuilder.cpp
        GamePlayerBuilder.cpp
        GameEngine.cpp
        GamePlayerOutput.cpp
)
target_link_libraries(game_engine network)

install(TARGETS game_engine
               RUNTIME DESTINATION bin
               LIBRARY DESTINATION lib
               ARCHIVE DESTINATION lib/static
)