#ifndef DIPLOMAMSU_READDATA_H

#include <bits/types/FILE.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DIPLOMAMSU_READDATA_H

FILE *get_file(char *filename);

void print_array_of_points(float *array, int number_of_cell, int number_of_coordinates_of_cells);

void write_result_to_file(char *filename, float *vector_of_points, int number_of_columns, int number_of_rows);

void print_figure_area(float *vector_of_cell_area, int number_of_cell);

#endif