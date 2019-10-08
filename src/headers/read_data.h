#include <bits/types/FILE.h>

#ifndef DIPLOMAMSU_READDATA_H
#define DIPLOMAMSU_READDATA_H
#endif

const char *path_to_data_directory = "../resource/data/";

struct Array_of_points {
    unsigned number_of_cell, total_number_of_coordinates;
    float *array;
};

FILE* get_file(char* filename);

struct Array_of_points *get_array_of_cells(FILE *file);

void print_array_of_points(float* array, unsigned number_of_cell, unsigned number_of_coordinates_of_cells);

float* get_collocatoin_points(float* array_of_points, unsigned number_of_cells);

void write_result_to_file(char *filename, float *vector_of_points, int number_of_columns, int number_of_rows);
