cmake_minimum_required(VERSION 3.19)
project(baproef)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(baproef
        iterator_interface.cpp
        iterator_interface.h
        btree.h
        map.h
        set.h
        genericJoin.cpp
        genericJoin.h
        HyperGraph.cpp
        HyperGraph.h
        join.cpp
        join.h
        main.cpp
        nestedLoopJoin.cpp
        nestedLoopJoin.h
        sortMergeJoin.cpp
        sortMergeJoin.h
        timer.cpp
        timer.h
        vectorUtil.cpp
        vectorUtil.h)
