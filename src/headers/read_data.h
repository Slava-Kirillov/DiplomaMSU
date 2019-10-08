#include <bits/types/FILE.h>

#ifndef DIPLOMAMSU_READDATA_H
#define DIPLOMAMSU_READDATA_H

#endif //DIPLOMAMSU_READDATA_H

const char *path_to_data_directory = "../resource/data/";

struct Array_of_points {
    unsigned number_of_cell, number_of_points;
    float *array;
};

FILE* get_file(char* filename);

struct Array_of_points *get_array_of_cells(FILE *file);

void print_array_of_points(float* array, unsigned number_of_cell, unsigned number_of_coordinates_of_cells);

float* get_collocatoin_points(float* array_of_points, unsigned number_of_cells);
