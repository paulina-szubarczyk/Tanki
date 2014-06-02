cmake_minimum_required(VERSION 2.8)
project( GameEngineLib )

find_package(PythonLibs)

include_directories(
        ${Message_BINARY_DIR}
        ${NetworkLib_SOURCE_DIR}
        ${Execs_SOURCE_DIR}
        ${PYTHON_INCLUDE_DIRS})

add_library(game_engine 
        BigGameShip.cpp 
        Field.cpp 
        FieldsUpdater.cpp 
        Game.cpp
        Gameboard.cpp   
        GameEngine.cpp     
        GamePlayer.cpp
        GamePlayerBuilder.cpp
        ShipFactoryMethod.cpp
        SmallGameShip.cpp 
        PyGameConfig.cpp
)
target_link_libraries(game_engine 
        network 
        message 
        ${PYTHON_LIBRARIES}
)

install(TARGETS game_engine
               RUNTIME DESTINATION bin
               LIBRARY DESTINATION lib
               ARCHIVE DESTINATION lib/static
)