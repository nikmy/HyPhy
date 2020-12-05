cmake_minimum_required(VERSION 3.16)
project(HyPhy C)

set(CMAKE_C_STANDARD 99)

add_executable(HyPhy parser.c
        utf8-io.h utf8-io.c utf8-rus.h utf8-rus.c parser.h main.c)