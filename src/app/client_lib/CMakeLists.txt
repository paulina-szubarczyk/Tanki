cmake_minimum_required(VERSION 2.8)
project( ClientLib )

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_library(lib_client ship.cpp)
target_link_libraries(lib_client ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
