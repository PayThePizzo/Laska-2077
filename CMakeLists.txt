cmake_minimum_required(VERSION 3.16)
project(Laska-2077 C)

set(CMAKE_C_STANDARD 90)    #standard ANSI C 90
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -pedantic")   #control of ansi c
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")   #release version settings

add_executable(Laska-2077
        laska.c
        main.c)

#Laska Ready
#Final
