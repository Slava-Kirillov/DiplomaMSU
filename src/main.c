#include <stdio.h>
#include <float.h>
#include <bits/types/FILE.h>
#include <malloc.h>
#include <string.h>

const char *path_to_data_directory = "../resource/data/";
const unsigned number_of_coordinates = 3; //Количество координат у точки
const unsigned number_of_cell_vertices = 4;

struct Array_of_points {
    unsigned number_of_cell;
    float *array;
};

struct Array_of_points *get_array_of_cells(char *filename);

int main(int argc, char **argv) {

    struct Array_of_points *struct_of_cells = get_array_of_cells("sphere_30_50.dat");
    float *pointer_on_points_array = struct_of_cells->array;
    float coordinate = 0, initial_coordinate = 0;
    int number_of_cells = struct_of_cells->number_of_cell;

    //array_of_cell - массив ячеек
    float array_of_cell[number_of_cells][number_of_cell_vertices][number_of_coordinates];

    //array_of_collocation_points - массив точек коллокации
    float array_of_collocation_points[number_of_cells][number_of_coordinates];

    //i - перебор по ячейкам
    for (unsigned i = 0; i < number_of_cells; ++i) {
        //j - перебор по вершинам ячейки
        for (unsigned j = 0; j < number_of_cell_vertices; ++j) {
            //k - перебор по координатам вершины ячейки
            for (unsigned k = 0; k < number_of_coordinates; ++k) {
                array_of_cell[i][j][k] = *pointer_on_points_array;
                printf("%f", array_of_cell[i][j][k]);
                printf("%s", " ");
                pointer_on_points_array++;
            }
        }
        printf("%s", "\n");
    }

    for (unsigned i = 0; i < number_of_cells; ++i){
        for (unsigned j = 0; j < number_of_coordinates; ++j) {
            for (unsigned k = 0; k < number_of_cell_vertices; ++k) {
                coordinate = coordinate + array_of_cell[i][k][j];
            }
            array_of_collocation_points[i][j] = coordinate/4;
            coordinate = initial_coordinate;
        }
    }


    return 0;
}


struct Array_of_points *get_array_of_cells(char *filename) {
    unsigned number_of_cell, number_of_points, i = 0;
    float point;

    char *path_to_data_file = malloc(sizeof(char) * (strlen(filename) + strlen(path_to_data_directory)));

    strcat(path_to_data_file, path_to_data_directory);
    strcat(path_to_data_file, filename);

    FILE *file = fopen(path_to_data_file, "r");

    free(path_to_data_file);

    if (file == NULL) {
        printf("File reading error\n");
        return NULL;
    }
    fscanf(file, "%d", &number_of_cell);

    number_of_points = number_of_cell * 12;
    float array_of_points[number_of_points];

    while (1) {
        if (fscanf(file, "%f", &point) != EOF) {
            array_of_points[i] = point;
            i++;
        } else {
            fclose(file);
            break;
        }
    }

    struct Array_of_points *array_struct = malloc(
            sizeof(array_of_points) + sizeof(number_of_points) + sizeof(number_of_cell));

    array_struct->number_of_cell = number_of_cell;
    array_struct->array = array_of_points;

    return array_struct;
}