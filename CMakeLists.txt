cmake_minimum_required(VERSION 3.14)
project(DiplomaMSU)

set(CMAKE_C_STANDARD 99)

add_executable(DiplomaMSU
        src/main.c
        src/data_gen.c
        src/read_write_print.c
        src/computation_service.c
        src/include/data_gen.h
        src/include/read_write_print.h
        src/include/computation_service.h)
target_link_libraries(DiplomaMSU pthread m)