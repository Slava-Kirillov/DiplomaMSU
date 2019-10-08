#include "headers/secondary_functions.h"

#define WRITE_TO_FILE 1 //Печать результата в файл

int main(int argc, char **argv) {

    FILE *file = get_file("sphere_30_50.dat");

    if (file != NULL) {
        struct Array_of_points *struct_of_cells = get_array_of_cells(file);
        float *vector_of_points = struct_of_cells->array;

        if (WRITE_TO_FILE) {
            write_result_to_file("sphere.dat", vector_of_points,
                                 struct_of_cells->number_of_coordinates_at_point,
                                 struct_of_cells->total_number_of_coordinates /
                                 struct_of_cells->number_of_coordinates_at_point);
        }

        float *vector_of_collocation_points = get_collocation_points(vector_of_points,
                                                                     struct_of_cells->number_of_cell);

        if (WRITE_TO_FILE) {
            write_result_to_file("collocation_points.dat", vector_of_collocation_points,
                                 struct_of_cells->number_of_coordinates_at_point,
                                 struct_of_cells->number_of_cell);
        }
    }

    return 0;
}