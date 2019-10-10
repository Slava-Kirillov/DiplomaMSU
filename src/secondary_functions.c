#include <bits/types/FILE.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "headers/secondary_functions.h"

const char *path_to_data_directory = "../resource/data/";

void print_array_of_points(float *array, int number_of_cell, int number_of_coordinates_of_cells) {
    int k = 0, i, j;
    for (i = 0; i < number_of_cell; ++i) {
        for (j = 0; j < number_of_coordinates_of_cells; ++j) {
            printf("%f ", array[k]);
            ++k;
        }
        printf("%s", "\n");
    }
}

struct_of_points *get_array_of_cells(FILE *file) {

    int number_of_cell, total_number_of_points, i = 0, j, number_of_coordinates_of_cells, k;
    char line[128], *p;
    float float_line[12], *array_of_points, *pointer_of_array;

    number_of_coordinates_of_cells = NUMBER_OF_COORDINATES_AT_POINT * NUMBER_OF_POINTS_PER_CELL;
    array_of_points = malloc(sizeof(float) * number_of_coordinates_of_cells);
    pointer_of_array = array_of_points;
    k = 0;
    while (!feof(file)) {
        if (fgets(line, 126, file)) {
            p = strtok(line, " ");
            for (i = 0; i < 12; ++i) {
                if (p == NULL || !strcmp(p, "\n")) {
                    break;
                }
                sscanf(p, "%f", &float_line[i]);
                p = strtok(NULL, " ");

                if (i == 11) {
                    for (int j = 0; j < 12; ++j) {
                        pointer_of_array[j] = float_line[j];
                    }
                    k += 12;
                    array_of_points = realloc(array_of_points, sizeof(float) * (k + number_of_coordinates_of_cells));
                    pointer_of_array = array_of_points + k;
                }
            }
        }
    }

    total_number_of_points = k;
    number_of_cell = total_number_of_points / number_of_coordinates_of_cells;

    if (PRINT_READ_DATA) {
        print_array_of_points(array_of_points, number_of_cell, number_of_coordinates_of_cells);
    }

    struct_of_points *array_struct = malloc(
            sizeof(float) * total_number_of_points + sizeof(total_number_of_points) + sizeof(number_of_cell));

    array_struct->number_of_cell = number_of_cell;
    array_struct->total_number_of_coordinates = total_number_of_points;
    array_struct->array = array_of_points;
    array_struct->number_of_coordinates_at_point = NUMBER_OF_COORDINATES_AT_POINT;

    return array_struct;
}

FILE *get_file(char *filename) {
    char *path_to_data_file = malloc(sizeof(char) * (strlen(filename) + strlen(path_to_data_directory)));

    strcat(path_to_data_file, path_to_data_directory);
    strcat(path_to_data_file, filename);

    FILE *file = fopen(path_to_data_file, "r");

    free(path_to_data_file);

    if (file == NULL) {
        perror("File reading error\n");
        exit(EXIT_FAILURE);
    }

    return file;
}

float *get_collocation_points(float *vector_of_points, int number_of_cells) {
    float coordinate = 0, initial_coordinate = 0;
    float array_of_collocation_points[number_of_cells][NUMBER_OF_COORDINATES_AT_POINT];

    MACROS_GET_ARRAY_CELL(vector_of_points, number_of_cells)

    float *return_array = malloc(sizeof(float) * number_of_cells * NUMBER_OF_COORDINATES_AT_POINT);
    float *pointer_to_array = return_array;
    for (int i = 0; i < number_of_cells; ++i) {
        for (int j = 0; j < NUMBER_OF_COORDINATES_AT_POINT; ++j) {
            for (int k = 0; k < NUMBER_OF_POINTS_PER_CELL; ++k) {
                coordinate = coordinate + array_of_cell[i][k][j];
            }
            *pointer_to_array = coordinate / 4;
            pointer_to_array++;
            array_of_collocation_points[i][j] = coordinate / 4;
            coordinate = initial_coordinate;
        }
    }

    return return_array;
}

float *get_array_of_vec_norm(float *vector_of_points, float *vector_of_collocation_points, int number_of_cells) {
    //get array_of_cell
    MACROS_GET_ARRAY_CELL(vector_of_points, number_of_cells)

    //get array_of_collocation_points
    MACROS_GET_ARRAY_COLLOCATION_POINTS(vector_of_collocation_points, number_of_cells)

    for (int i = 0; i < number_of_cells; i++) {
        float colloc_point[NUMBER_OF_COORDINATES_AT_POINT],
                a2_point[NUMBER_OF_COORDINATES_AT_POINT],
                a3_point[NUMBER_OF_COORDINATES_AT_POINT];
        for (int j = 0; j < NUMBER_OF_COORDINATES_AT_POINT; ++j) {
            colloc_point[j] = array_of_collocation_points[i][j];
            a2_point[j] = array_of_cell[i][2][j];
            a3_point[j] = array_of_cell[i][3][j];
        }

        //TODO: продолжить

    }
}

float get_cell_area(float *cell) {
    float diag1[NUMBER_OF_COORDINATES_AT_POINT], diag2[NUMBER_OF_COORDINATES_AT_POINT];
    int i = 0, j = 0;

    j = (NUMBER_OF_COORDINATES_AT_POINT * NUMBER_OF_POINTS_PER_CELL) / 2;

    diag1[0] = *(cell + i++) - *(cell + j++);
    diag1[1] = *(cell + i++) - *(cell + j++);
    diag1[2] = *(cell + i++) - *(cell + j++);

    diag2[0] = *(cell + i++) - *(cell + j++);
    diag2[1] = *(cell + i++) - *(cell + j++);
    diag2[2] = *(cell + i) - *(cell + j);

    float diag1_length = sqrtf(diag1[0] * diag1[0] + diag1[1] * diag1[1] + diag1[2] * diag1[2]);
    float diag2_length = sqrtf(diag2[0] * diag2[0] + diag2[1] * diag2[1] + diag2[2] * diag2[2]);
    float scalar_mult_diag1_diag2 = diag1[0] * diag2[0] + diag1[1] * diag2[1] + diag1[2] * diag2[2];
    return diag1_length *
           diag2_length *
           sqrtf(1 - powf((scalar_mult_diag1_diag2 / (diag1_length * diag2_length)), 2)) / 2;
}

float *get_array_of_cell_area(float *vector_of_points, int number_of_cells) {
    float *array_of_cells_area = malloc(sizeof(float) * number_of_cells);
    float *cell = malloc(sizeof(float) * NUMBER_OF_POINTS_PER_CELL * NUMBER_OF_COORDINATES_AT_POINT);
    double areaSum = 0;

    MACROS_GET_ARRAY_CELL(vector_of_points, number_of_cells)

    for (int i = 0; i < number_of_cells; ++i) {
        int counter = 0;
        for (int j = 0; j < NUMBER_OF_POINTS_PER_CELL; ++j) {
            for (int k = 0; k < NUMBER_OF_COORDINATES_AT_POINT; ++k) {
                *(cell + counter++) = array_of_cell[i][j][k];
            }
        }
        array_of_cells_area[i] = get_cell_area(cell);
        areaSum += array_of_cells_area[i];
    }
    return array_of_cells_area;
}

void write_result_to_file(char *filename, float *vector_of_points, int number_of_columns, int number_of_rows) {
    char *path_to_data_file = malloc(sizeof(char) * (strlen(filename) + strlen(path_to_data_directory)));
    memset(path_to_data_file, 0, sizeof(char) * (strlen(filename) + strlen(path_to_data_directory)));

    strcat(path_to_data_file, path_to_data_directory);
    strcat(path_to_data_file, filename);

    FILE *file = fopen(path_to_data_file, "w");

    if (file == NULL) {
        perror(path_to_data_file);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < number_of_rows; ++i) {
        for (int j = 0; j < number_of_columns; ++j) {
            fprintf(file, "%f ", *vector_of_points);
            vector_of_points++;
        }
        fprintf(file, "%s", "\n");
    }

    fclose(file);
}

