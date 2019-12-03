cmake_minimum_required(VERSION 3.14)
project(DiplomaMSU)

set(CMAKE_C_STANDARD 99)

add_executable(main src/main.c src/headers/read_write_print.h src/read_write_print.c src/headers/data_gen.h src/data_gen.c src/headers/computation_service.h)
target_link_libraries(main m)