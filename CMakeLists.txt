

cmake_minimum_required(VERSION 3.6)
project(Maze VERSION 1.0)


FIND_PACKAGE( OpenCV REQUIRED )                              
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

add_executable(new_maze coordinates.cpp maze.cpp final_maze.cpp picture.cpp new_maze.cpp)
TARGET_LINK_LIBRARIES (new_maze ${OpenCV_LIBS})
