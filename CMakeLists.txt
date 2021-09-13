cmake_minimum_required(VERSION 3.19)
project(Base_classes)

set(CMAKE_CXX_STANDARD 14)

add_executable(Base_classes
        main.cpp
        Timer/myTimer.cpp Timer/myTimer.h)

#add_executable(Base_classes test.cpp)