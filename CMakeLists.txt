cmake_minimum_required(VERSION 3.16)
project("NAME OF PROJECT" C)

set(CMAKE_C_STANDARD 90)    #standard ANSI C 90
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -pedantic")   #control of ansi c
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")   #release version settings

add_executable("NAME OF PROJECT"
        laska.c
        main.c)

#Laska Ready

