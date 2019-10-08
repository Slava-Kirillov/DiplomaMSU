#include <stdio.h>
#include <float.h>
#include <bits/types/FILE.h>
#include <malloc.h>
#include <string.h>

const char *path_to_data_directory = "../resource/data/";
const unsigned number_of_coordinates_at_point = 3; //Количество координат у точки
const unsigned number_of_points_per_cell = 4; //Количество точек у ячейки

struct Array_of_points {
    unsigned number_of_cell;
    float *array;
};

struct Array_of_points *get_array_of_cells(char *filename);

int main(int argc, char **argv) {

    struct Array_of_points *struct_of_cells = get_array_of_cells("sphere_30_50.dat");
//    float coordinate = 0, initial_coordinate = 0;
//    int number_of_cells = struct_of_cells->number_of_cell;
//

//    float array_of_cell[number_of_cells][number_of_points_per_cell][number_of_coordinates_at_point];
//

//    float array_of_collocation_points[number_of_cells][number_of_coordinates_at_point];
//

//    for (unsigned i = 0; i < number_of_cells; ++i) {

//        for (unsigned j = 0; j < number_of_points_per_cell; ++j) {

//            for (unsigned k = 0; k < number_of_coordinates_at_point; ++k) {
//                array_of_cell[i][j][k] = *pointer_on_points_array;
//                printf("%f", *pointer_on_points_array);
//                printf("%s", " ");
//                pointer_on_points_array++;
//            }
//        }
//        printf("%s", "\n");
//    }
//
//    for (unsigned i = 0; i < number_of_cells; ++i){
//        for (unsigned j = 0; j < number_of_coordinates_at_point; ++j) {
//            for (unsigned k = 0; k < number_of_points_per_cell; ++k) {
//                coordinate = coordinate + array_of_cell[i][k][j];
//            }
//            array_of_collocation_points[i][j] = coordinate/4;
//            coordinate = initial_coordinate;
//        }
//    }
//
//
    return 0;
}


struct Array_of_points *get_array_of_cells(char *filename) {
    unsigned number_of_cell, total_number_of_points, i = 0, j;
    float point;
    char line[128];
    char *p;
    float float_line[12], *array_of_cell, *pointer_of_array;

    int number_of_coordinates_of_cells = number_of_coordinates_at_point * number_of_points_per_cell, k = 0;

    char *path_to_data_file = malloc(sizeof(char) * (strlen(filename) + strlen(path_to_data_directory)));

    strcat(path_to_data_file, path_to_data_directory);
    strcat(path_to_data_file, filename);

    FILE *file = fopen(path_to_data_file, "r");

    free(path_to_data_file);

    if (file == NULL) {
        printf("File reading error\n");
        return NULL;
    }

    array_of_cell = malloc(sizeof(float) * number_of_coordinates_of_cells);
    pointer_of_array = array_of_cell;
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
                    array_of_cell = realloc(array_of_cell, sizeof(float) * (k + number_of_coordinates_of_cells));
                    pointer_of_array = array_of_cell + k;
                }
            }
        }
    }

    total_number_of_points = k;
    number_of_cell = total_number_of_points / number_of_coordinates_of_cells;

    k = 0;
    for (i = 0; i < number_of_cell; ++i) {
        for (j = 0; j < number_of_coordinates_of_cells; ++j) {
            printf("%f ", array_of_cell[k]);
            ++k;
        }
        printf("%s", "\n");
    }

//
//    struct Array_of_points *array_struct = malloc(
//            sizeof(array_of_points) + sizeof(total_number_of_points) + sizeof(number_of_cell));
//
//    array_struct->number_of_cell = number_of_cell;
//    array_struct->array = array_of_points;
//
//    return array_struct;
    return NULL;
}