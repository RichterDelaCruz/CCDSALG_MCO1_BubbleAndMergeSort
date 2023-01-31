cmake_minimum_required(VERSION 3.21)
project(CCDSALG_MP C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(CCDSALG_MP
        "Bubble Sort/bubbleSortFinal.c")

#[[add_executable(CCDSALG_MP#
        "Merge Sort/mergeSortFinal.c")]]

#[[add_executable(CCDSALG_MP
        "Selection Sort/selectionSort.c")]]
