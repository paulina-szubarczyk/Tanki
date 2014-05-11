cmake_minimum_required(VERSION 2.8)
project( GameEngineLib )

add_library(lib_game_engine  Field.cpp GameShip.cpp SmallGameShip.cpp)
# BigGameShip.cpp 