cmake_minimum_required(VERSION 3.17)
project(Exc03)

set(CMAKE_CXX_STANDARD 14)

add_executable(Exc03 main.cpp Controller.cpp Controller.h Model.cpp Model.h View.cpp View.h Geometry.cpp Geometry.h Graph.cpp Graph.h Warehouse.cpp Warehouse.h)