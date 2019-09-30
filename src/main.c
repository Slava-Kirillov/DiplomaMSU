#include <stdio.h>
#include <float.h>
#include <bits/types/FILE.h>

double *get_array_of_points(char *filename) {
    int numbers_of_cell, number_of_points, i = 0;
    float point;

    FILE *file = fopen(filename, "r");
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
            break;
        }
    }
    return array_of_points;
}

int main(int argc, char **argv) {
    double *array_of_points = get_array_of_points("../resource/data/sphere_30_50.dat");
    

    return 0;
}