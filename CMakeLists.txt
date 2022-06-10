cmake_minimum_required(VERSION 3.17)
project(Exc03)

set(CMAKE_CXX_STANDARD 14)

add_executable(Exc03 main.cpp Controller.cpp Controller.h Model.cpp Model.h View.cpp View.h Geometry.cpp Geometry.h
        Warehouse.cpp Warehouse.h Chopper.h Chopper.cpp Sim_obj.cpp Sim_obj.h StateTrooper.cpp StateTrooper.h Vehicle.h Vehicle.cpp
        Truck.h Truck.cpp Track_base.h Track_base.cpp)