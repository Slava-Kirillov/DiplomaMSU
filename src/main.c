#include "headers/secondary_functions.h"

#define WRITE_TO_FILE 1 //Печать результата в файл
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"

void print_figure_area(float *vector_of_cell_area, int number_of_cell);

int main(int argc, char **argv) {

    if (NUMBER_OF_POINTS_PER_CELL % 2 != 0) {
        perror("Number of points per cell is not even");
        exit(EXIT_FAILURE);
    }

    FILE *file = get_file("sphere_30_50.dat");

    struct_of_points *struct_of_cells = get_array_of_cells(file);
    int number_of_cell = struct_of_cells->number_of_cell;

    float *vector_of_points = struct_of_cells->array;
    float *vector_of_collocation_points = get_collocation_points(vector_of_points, number_of_cell);
    float *vector_of_cell_area = get_array_of_cell_area(vector_of_points, number_of_cell);
    float *vector_of_normals = get_array_of_vec_norm(vector_of_points, vector_of_cell_area, number_of_cell);

    print_figure_area(vector_of_cell_area, number_of_cell);

    if (WRITE_TO_FILE) {
        write_result_to_file("collocation_points.dat", vector_of_collocation_points,
                             struct_of_cells->number_of_coordinates_at_point,
                             struct_of_cells->number_of_cell);
        write_result_to_file("sphere.dat", vector_of_points,
                             struct_of_cells->number_of_coordinates_at_point,
                             struct_of_cells->total_number_of_coordinates /
                             struct_of_cells->number_of_coordinates_at_point);
        write_result_to_file("cell_area.dat", vector_of_cell_area,
                             1, struct_of_cells->number_of_cell);
        write_result_to_file("normal_vectors.dat", vector_of_normals,
                             struct_of_cells->number_of_coordinates_at_point,
                             struct_of_cells->number_of_cell);
    }

    return 0;
}

void print_figure_area(float *vector_of_cell_area, int number_of_cell) {
    float area = 0;
    for (int i = 0; i < number_of_cell; ++i) {
        area += *vector_of_cell_area;
        vector_of_cell_area++;
    }

    printf(GRN "Площадь фигуры по данным из файла: " RED "%f\n", area);
    printf(GRN "Площадь фигуры по формуле S = 4*Pi*R: " RED "%f\n", M_PI * 4);
    printf(GRN "Разность: " RED "%f" RESET, fabsf(area - M_PI * 4));
}