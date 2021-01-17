cmake_minimum_required(VERSION 3.16)
project(Mini_Lasca_C C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -pedantic")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")

add_executable(Mini_Lasca_C
        laska.c
        main.c)

#Laska Ready