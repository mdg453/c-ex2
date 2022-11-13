cmake_minimum_required(VERSION 3.23)
project(ex2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex2
        main.c
        ProductBST.h)
