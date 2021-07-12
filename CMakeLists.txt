cmake_minimum_required(VERSION 3.19)
project(Base_classes)

set(CMAKE_CXX_STANDARD 14)

add_executable(Base_classes main.cpp DynamicArray/myDynamicArray.cpp DynamicArray/myDynamicArray.h Sequence/mySequence.h Sequence/myArraySequence.h)