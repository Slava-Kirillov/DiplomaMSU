#include <stdio.h>
#include <float.h>
#include <bits/types/FILE.h>
#include <malloc.h>
#include <string.h>

const char* path_to_data_directory = "../resource/data/";

struct Array_of_points{
    int array_size;
    float *array;
};

struct Array_of_points *get_array_of_points(char *filename);
float *get_array_of_cell(struct Array_of_points* array_of_points);

int main(int argc, char **argv) {
    struct Array_of_points *array_of_points = get_array_of_points("sphere_30_50.dat");
    float *array_of_cell = get_array_of_cell(array_of_points);

    return 0;
}

/*
 * Формирование массива с координатами точек тела из файла
 * filename - имя файла
 */
struct Array_of_points *get_array_of_points(char *filename) {
    int numbers_of_cell, number_of_points, i = 0;
    float point;
//    char * path_to_data_file = malloc(sizeof(char) * (strlen(filename) + strlen(path_to_data_directory)));
    char * path_to_data_file = malloc(sizeof(char) * (strlen(filename) + strlen(path_to_data_directory)));

    strcat(path_to_data_file, path_to_data_directory);
    strcat(path_to_data_file, filename);

    FILE *file = fopen(path_to_data_file, "r");

    free(path_to_data_file);

    if (file == NULL) {
        printf("File reading error\n");
        return NULL;
    }
    fscanf(file, "%d", &numbers_of_cell);

    number_of_points = numbers_of_cell * 12;
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
    struct Array_of_points *array_struct = malloc(sizeof(array_of_points) + sizeof(number_of_points));

    array_struct->array_size = number_of_points;
    array_struct->array = array_of_points;
    return array_struct;
}


float *get_array_of_cell(struct Array_of_points *array_of_points){
    array_of_points;
    return NULL;
}