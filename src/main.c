#include "include/read_write_print.h"
#include "include/data_gen.h"
#include "include/computation_service.h"

#define WRITE_TO_FILE 1 //Печать результата в файл

void write_all_result_in_files(double *collocation_points,
                               double *cell_area,
                               vectors_in_cells *vectors,
                               struct_of_points *struct_of_points) {
    if (WRITE_TO_FILE) {
        write_result_to_file(
                "collocation_points.dat",
                collocation_points,
                struct_of_points->number_of_coordinates_at_point,
                struct_of_points->number_of_cell
        );
        write_result_to_file(
                "sphere.dat",
                struct_of_points->array,
                struct_of_points->number_of_coordinates_at_point,
                struct_of_points->total_number_of_coordinates /
                struct_of_points->number_of_coordinates_at_point
        );
        write_result_to_file(
                "cell_area.dat",
                cell_area,
                1,
                struct_of_points->number_of_cell
        );
        write_result_to_file(
                "normal_vectors.dat",
                vectors->normals,
                struct_of_points->number_of_coordinates_at_point,
                struct_of_points->number_of_cell
        );
        write_result_to_file(
                "tau1_vectors.dat",
                vectors->tau1,
                struct_of_points->number_of_coordinates_at_point,
                struct_of_points->number_of_cell
        );
        write_result_to_file(
                "tau2_vectors.dat",
                vectors->tau2,
                struct_of_points->number_of_coordinates_at_point,
                struct_of_points->number_of_cell
        );
    }
}

int main(int argc, char **argv) {

    if (NUMBER_OF_POINTS_PER_CELL % 2 != 0) {
        perror("Number of points per cell is not even");
        exit(EXIT_FAILURE);
    }


    // открываем файл для чтения
    FILE *file = get_file("25_50_(2050).dat");

    struct_of_points *struct_of_points = get_array_of_points(file);

    // закрываем файл
    fclose(file);

    // получить массив точек коллокации
    double *collocation_points = get_collocation_points(struct_of_points->array, struct_of_points->number_of_cell);

    // получить массив площадей ячеек разбиения
    double *cell_area = get_array_of_cell_area(struct_of_points->array, struct_of_points->number_of_cell);

    // получить структуры с массивами векторов для ячеек
    vectors_in_cells *vectors = get_array_of_vec(struct_of_points->array, struct_of_points->number_of_cell);

    

    // запись всех данных в файлы
//    write_all_result_in_files(collocation_points, cell_area, vectors, struct_of_points);

    // вывод площади фигуры
//    print_figure_area(cell_area, struct_of_points->number_of_cell);

    return 0;
}