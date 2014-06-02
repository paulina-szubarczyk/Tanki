cmake_minimum_required(VERSION 2.8)
project( Execs )

include_directories(${Message_BINARY_DIR})
include_directories(${NetworkLib_SOURCE_DIR})
include_directories(${ClientLib_SOURCE_DIR})
include_directories(${GameEngineLib_SOURCE_DIR})


add_library(exec 
        PlayerInput.cpp 
        PlayerOutput.cpp
        ConnectionBridge.cpp 
        ClientInput.cpp 
        ClientOutput.cpp
)
target_link_libraries(exec network game_engine lib_client)

add_executable(server server.cpp)
target_link_libraries(server exec)

add_executable(gui gui.cpp)
target_link_libraries(gui exec)

install(TARGETS server gui
               RUNTIME DESTINATION bin
               LIBRARY DESTINATION lib
               ARCHIVE DESTINATION lib/static
)
