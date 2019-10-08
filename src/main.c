#include "secondary_functions.h"

#define WRITE_TO_FILE 0 //Печать результата в файл

int main(int argc, char **argv) {

    FILE *file = get_file("sphere_30_50.dat");

    if (file != NULL) {
        struct Array_of_points *struct_of_cells = get_array_of_cells(file);
        float *vector_of_points = struct_of_cells->array;

        if (WRITE_TO_FILE) {
            write_result_to_file("sphere.dat", vector_of_points,
                                 NUMBER_OF_COORDINATES_AT_POINT,
                                 struct_of_cells->total_number_of_coordinates / NUMBER_OF_COORDINATES_AT_POINT);
        }

        float *vector_of_collacation_points = get_collocatoin_points(vector_of_points, struct_of_cells->number_of_cell);

        if (WRITE_TO_FILE) {
            write_result_to_file("collacation_points.dat", vector_of_collacation_points,
                                 NUMBER_OF_COORDINATES_AT_POINT,
                                 struct_of_cells->number_of_cell);
        }
    }

    return 0;
}