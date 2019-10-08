#include <bits/types/FILE.h>
#include <malloc.h>
#include <string.h>

#define NUMBER_OF_POINTS_PER_CELL 4 //Количество точек у ячейки
#define PRINT_READ_DATA 0 //Печть данных, прочитанных из файла
#define NUMBER_OF_COORDINATES_AT_POINT 3 //Количество координат у точки

const char *path_to_data_directory = "../resource/data/";

struct Array_of_points {
    unsigned number_of_cell,
            total_number_of_coordinates,
            number_of_coordinates_at_point;
    float *array;
};

void print_array_of_points(float *array, unsigned number_of_cell, unsigned number_of_coordinates_of_cells) {
    int k = 0, i, j;
    for (i = 0; i < number_of_cell; ++i) {
        for (j = 0; j < number_of_coordinates_of_cells; ++j) {
            printf("%f ", array[k]);
            ++k;
        }
        printf("%s", "\n");
    }
}

struct Array_of_points *get_array_of_cells(FILE *file) {
    unsigned number_of_cell, total_number_of_points, i = 0, j, number_of_coordinates_of_cells, k;
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

    struct Array_of_points *array_struct = malloc(
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
        printf("File reading error\n");
        return NULL;
    }

    return file;
}

float *get_collocation_points(float *array_of_points, unsigned number_of_cells) {
    float coordinate = 0, initial_coordinate = 0;
    float array_of_cell[number_of_cells][NUMBER_OF_POINTS_PER_CELL][NUMBER_OF_COORDINATES_AT_POINT];
    float array_of_collocation_points[number_of_cells][NUMBER_OF_COORDINATES_AT_POINT];

    float *pointer_on_points_array = array_of_points;
    for (unsigned i = 0; i < number_of_cells; ++i) {
        for (unsigned j = 0; j < NUMBER_OF_POINTS_PER_CELL; ++j) {
            for (unsigned k = 0; k < NUMBER_OF_COORDINATES_AT_POINT; ++k) {
                array_of_cell[i][j][k] = *pointer_on_points_array;
                pointer_on_points_array++;
            }
        }
    }


    float *return_array = malloc(sizeof(float) * number_of_cells * NUMBER_OF_COORDINATES_AT_POINT);
    float *pointer_to_array = return_array;
    for (unsigned i = 0; i < number_of_cells; ++i) {
        for (unsigned j = 0; j < NUMBER_OF_COORDINATES_AT_POINT; ++j) {
            for (unsigned k = 0; k < NUMBER_OF_POINTS_PER_CELL; ++k) {
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

void write_result_to_file(char *filename, float *vector_of_points, int number_of_columns, int number_of_rows) {
    char *path_to_data_file = malloc(sizeof(char) * (strlen(filename) + strlen(path_to_data_directory)));

    strcat(path_to_data_file, path_to_data_directory);
    strcat(path_to_data_file, filename);

    FILE *file = fopen(path_to_data_file, "w");

    for (int i = 0; i < number_of_rows; ++i) {
        for (int j = 0; j < number_of_columns; ++j) {
            fprintf(file, "%f ", *vector_of_points);
            vector_of_points++;
        }
        fprintf(file, "%s", "\n");
    }

    fclose(file);
}

