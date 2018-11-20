cmake_minimum_required(VERSION 3.12)
project(graph)

set(CMAKE_CXX_STANDARD 14)

include_directories(INCLUDE)

add_executable(graph
        INCLUDE/graph.h
        INCLUDE/list.h
        INCLUDE/main.h
        SRC/graph.c
        SRC/list.c
        SRC/main.c
        Makefile
        README.md SRC/linkedlist.c INCLUDE/linkedlist.h)
