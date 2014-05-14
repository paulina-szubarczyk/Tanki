cmake_minimum_required(VERSION 2.8)
project( GameEngineLib )

add_library(game_engine 
        Field.cpp 
        GameShip.cpp 
        SmallGameShip.cpp 
        BigGameShip.cpp 
        HitObserver.cpp
        FieldsUpdater.cpp 
        ShipObserver.cpp 
        Gameboard.cpp
)

install(TARGETS game_engine
               RUNTIME DESTINATION bin
               LIBRARY DESTINATION lib
               ARCHIVE DESTINATION lib/static
)