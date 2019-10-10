#ifndef DIPLOMAMSU_READDATA_H

#include <bits/types/FILE.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DIPLOMAMSU_READDATA_H
#define NUMBER_OF_POINTS_PER_CELL 4U //Количество точек у ячейки
#define PRINT_READ_DATA 0U //Печть данных, прочитанных из файла
#define NUMBER_OF_COORDINATES_AT_POINT 3U //Количество координат у точки

#define MACROS_GET_ARRAY_CELL(vector_of_points, number_of_cells) \
    float array_of_cell[number_of_cells][NUMBER_OF_POINTS_PER_CELL][NUMBER_OF_COORDINATES_AT_POINT]; \
    for (int i = 0; i < number_of_cells; ++i) { \
        for (int j = 0; j < NUMBER_OF_POINTS_PER_CELL; ++j) { \
            for (int k = 0; k < NUMBER_OF_COORDINATES_AT_POINT; ++k) { \
                array_of_cell[i][j][k] = *(vector_of_points++); \
            } \
        } \
     } \

#define MACROS_GET_ARRAY_COLLOCATION_POINTS(vector_of_collocation_points, number_of_cells) \
    float array_of_collocation_points[number_of_cells][NUMBER_OF_COORDINATES_AT_POINT]; \
    for (int i = 0; i < number_of_cells; i++) { \
        for (int j = 0; j < NUMBER_OF_COORDINATES_AT_POINT; j++) { \
            array_of_collocation_points[i][j] = *(vector_of_collocation_points++); \
        } \
    } \

typedef struct Array_of_points {
    unsigned number_of_cell,
            total_number_of_coordinates,
            number_of_coordinates_at_point;
    float *array;
} struct_of_points;

FILE *get_file(char *filename);

struct_of_points *get_array_of_cells(FILE *file);

void print_array_of_points(float *array, int number_of_cell, int number_of_coordinates_of_cells);

float *get_collocation_points(float *array_of_points, int number_of_cells);

void write_result_to_file(char *filename, float *vector_of_points, int number_of_columns, int number_of_rows);

float *get_array_of_cell_area(float *vector_of_points, int number_of_cells);

#endif