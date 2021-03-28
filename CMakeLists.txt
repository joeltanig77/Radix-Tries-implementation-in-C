cmake_minimum_required(VERSION 3.17)
project(RadixTrees C)

set(CMAKE_C_STANDARD 99)

add_executable(RadixTrees main.c radixFunc.c radixFunc.h)