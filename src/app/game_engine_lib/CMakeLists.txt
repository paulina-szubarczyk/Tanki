cmake_minimum_required(VERSION 2.8)
project( GameEngineLib )

include_directories(${Message_BINARY_DIR})
include_directories(${NetworkLib_SOURCE_DIR})

add_library(game_engine 
        BigGameShip.cpp 
        ConnectionBridge.cpp
        Field.cpp 
        FieldsUpdater.cpp 
        Game.cpp
        Gameboard.cpp   
        GameEngine.cpp     
        GamePlayer.cpp
        GamePlayerBuilder.cpp
        GameShip.cpp 
        HitObserver.cpp
        PlayerBuilder.cpp
        PlayerOutput.cpp
        ShipFactoryMethod.cpp
        ShipObserver.cpp 
        SmallGameShip.cpp 
)
target_link_libraries(game_engine network message)

install(TARGETS game_engine
               RUNTIME DESTINATION bin
               LIBRARY DESTINATION lib
               ARCHIVE DESTINATION lib/static
)