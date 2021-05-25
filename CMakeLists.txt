cmake_minimum_required(VERSION 3.19)
project(baproef)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(baproef
        TrieIterator.cpp
        TrieIterator.h
        benchmark.cpp
        benchmark.h
        leapfrog_join.h
        leapfrog_join.cpp
        leapfrog_triejoin.h
        leapfrog_triejoin.cpp
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
