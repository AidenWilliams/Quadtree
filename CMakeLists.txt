cmake_minimum_required(VERSION 3.17)
project(Quadtree)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-march=native")

set(TARGET_H QuadTree.h)
SET(TARGET_S main.cpp QuadTree.cpp)


add_executable(Quadtree ${TARGET_S} ${TARGET_H})