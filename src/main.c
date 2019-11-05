#include "headers/read_write_print.h"
#include "headers/data_gen.h"

#define WRITE_TO_FILE 1 //Печать результата в файл

void print_figure_area(float *vector_of_cell_area, int number_of_cell);

int main(int argc, char **argv) {

    if (NUMBER_OF_POINTS_PER_CELL % 2 != 0) {
        perror("Number of points per cell is not even");
        exit(EXIT_FAILURE);
    }

    FILE *file = get_file("sphere_30_50.dat");

    struct_of_points *struct_of_cells = get_array_of_cells(file);

    fclose(file);

    int number_of_cell = struct_of_cells->number_of_cell;

    float *vector_of_points = struct_of_cells->array;
    float *vector_of_collocation_points = get_collocation_points(vector_of_points, number_of_cell);
    float *vector_of_cell_area = get_array_of_cell_area(vector_of_points, number_of_cell);
    vectors_in_cells *vectors = get_array_of_vec(vector_of_points, number_of_cell);

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
        write_result_to_file("normal_vectors.dat", vectors->normals,
                             struct_of_cells->number_of_coordinates_at_point,
                             struct_of_cells->number_of_cell);
        write_result_to_file("tau1_vectors.dat", vectors->tau1,
                             struct_of_cells->number_of_coordinates_at_point,
                             struct_of_cells->number_of_cell);
        write_result_to_file("tau2_vectors.dat", vectors->tau2,
                             struct_of_cells->number_of_coordinates_at_point,
                             struct_of_cells->number_of_cell);
    }
    print_figure_area(vector_of_cell_area, number_of_cell);

    return 0;
}