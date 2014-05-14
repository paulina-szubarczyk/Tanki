cmake_minimum_required(VERSION 2.8)
project( ClientLib )

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLUI REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} 
                     ${GLUT_INCLUDE_DIRS} 
                     ${GLUI_INCLUDE_DIRS}
)

add_library(lib_client ship.cpp)
target_link_libraries(lib_client ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLUI_LIBRARIES})


install(TARGETS lib_client
               RUNTIME DESTINATION bin
               LIBRARY DESTINATION lib
               ARCHIVE DESTINATION lib/static
)