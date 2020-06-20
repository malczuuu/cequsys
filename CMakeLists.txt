cmake_minimum_required(VERSION 3.10)
project(cequsys)

set(CMAKE_CXX_STANDARD 14)

add_executable(cequsys
        src/stringutil.cpp
        src/stringutil.hpp
        src/matrix.hpp
        src/loader.cpp
        src/loader.hpp
        src/main.cpp
        src/equsys.cpp src/equsys.hpp)
