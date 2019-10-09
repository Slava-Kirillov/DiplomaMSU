#ifndef DIPLOMAMSU_READDATA_H
#define DIPLOMAMSU_READDATA_H

#include <bits/types/FILE.h>
#include <malloc.h>
#include <string.h>

typedef struct Array_of_points {
    unsigned number_of_cell,
            total_number_of_coordinates,
            number_of_coordinates_at_point;
    float *array;
} struct_of_points;

FILE *get_file(char *filename);

struct_of_points *get_array_of_cells(FILE *file);

void print_array_of_points(float *array, unsigned number_of_cell, unsigned number_of_coordinates_of_cells);

float *get_collocation_points(float *array_of_points, unsigned number_of_cells);

void write_result_to_file(char *filename, float *vector_of_points, int number_of_columns, int number_of_rows);

float *get_cell_area(float* array_of_points, unsigned number_of_cells);

#endif