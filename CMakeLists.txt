cmake_minimum_required(VERSION 3.16)
project(Base_classes)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Base_classes
        main.cpp
        Timer/myTimer.cpp
        #test.cpp
        Sequence/ArraySequenceTest.cpp
        Tests/TestFuncs.cpp Tests/TestFuncs.h)

#add_executable(Base_classes test.cpp)