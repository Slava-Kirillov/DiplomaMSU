cmake_minimum_required(VERSION 3.14)
project(DiplomaMSU)

set(CMAKE_C_STANDARD 99)

add_executable(main src/main.c src/headers/secondary_functions.h src/secondary_functions.c)
target_link_libraries(main m)