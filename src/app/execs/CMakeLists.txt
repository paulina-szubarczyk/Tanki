cmake_minimum_required(VERSION 2.8)
project( Execs )

include_directories(${Message_BINARY_DIR})
include_directories(${NetworkLib_SOURCE_DIR})
include_directories(${ClientLib_SOURCE_DIR})
include_directories(${GameEngineLib_SOURCE_DIR})

add_executable(server server.cpp PlayerInput.cpp)
target_link_libraries(server network game_engine)

add_executable(client client.cpp )
target_link_libraries( client network )

add_executable(gui gui.cpp ClientInput.cpp ClientOutput.cpp)
target_link_libraries(gui lib_client network)

install(TARGETS client server gui
               RUNTIME DESTINATION bin
               LIBRARY DESTINATION lib
               ARCHIVE DESTINATION lib/static
)
