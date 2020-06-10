#include "include/read_write_print.h"

#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"

const char *path_to_data_directory = "../resource/data/";
const char *path_to_result_directory = "../resource/data/result/";

/**
 * Печать массива ячеек в терминал
 * @param array
 * @param number_of_cell
 * @param number_of_coordinates_of_cells
 */
void print_array_of_points(double *array, int number_of_cell, int number_of_coordinates_of_cells) {
    int k = 0, i, j;
    for (i = 0; i < number_of_cell; ++i) {
        for (j = 0; j < number_of_coordinates_of_cells; ++j) {
            printf("%f ", array[k]);
            ++k;
        }
        printf("%s", "\n");
    }
}

/**
 * Открыть файл для чтения
 * @param filename
 * @return
 */
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

/**
 * Печать результата в файл
 * @param filename
 * @param vector_of_points
 * @param number_of_columns
 * @param number_of_rows
 */
void write_result_to_file(char *filename, double *vector_of_points, int number_of_columns, int number_of_rows) {
    char *path_to_data_file = malloc(sizeof(char) * (strlen(filename) + strlen(path_to_result_directory)));
    memset(path_to_data_file, 0, sizeof(char) * (strlen(filename) + strlen(path_to_result_directory)));

    strcat(path_to_data_file, path_to_result_directory);
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

void print_figure_area(double *vector_of_cell_area, int number_of_cell) {
    double area = 0;
    for (int i = 0; i < number_of_cell; ++i) {
        area += *vector_of_cell_area;
        vector_of_cell_area++;
    }

    printf(GRN "Площадь фигуры по данным из файла: " RED "%f\n", area);
    printf(GRN "Площадь фигуры по формуле S = 4*Pi*R: " RED "%f\n", M_PI * 4);
    printf(GRN "Разность: " RED "%f" RESET, fabsf(area - M_PI * 4));
}