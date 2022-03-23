cmake_minimum_required(VERSION 3.21)
project(SudokuX C)

set(CMAKE_C_STANDARD 99)

add_executable(SudokuX main.c files.c files.h backtracking.c backtracking.h algorithms/helper.c algorithms/helper.h algorithms/nakedpairs.c algorithms/nakedpairs.h algorithms/hiddensingle.c algorithms/hiddensingle.c algorithms/hiddensingle.h algorithms/intersectionremoval.c algorithms/intersectionremoval.h algorithms/xwing.c algorithms/xwing.h)
