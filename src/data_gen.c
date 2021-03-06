#include "include/data_gen.h"
#include "include/read_write_print.h"


typedef struct Diag_of_cell {
    double *diag1;
    double *diag2;
} diag;

diag *get_diag_of_cell(const double *cell);

/**
 * Получить структуру с массивом ячеек разбиения
 * @param file
 * @return
 */
struct_of_points *get_array_of_points(FILE *file) {

    int number_of_cell, total_number_of_points, i = 0, j, number_of_coordinates_of_cells, k;
    char line[128], *p;
    double float_line[12], *array_of_points, *pointer_of_array;

    number_of_coordinates_of_cells = NUMBER_OF_COORDINATES_AT_POINT * NUMBER_OF_POINTS_PER_CELL;
    array_of_points = malloc(sizeof(double) * number_of_coordinates_of_cells);
    pointer_of_array = array_of_points;
    k = 0;
    while (!feof(file)) {
        if (fgets(line, 126, file)) {
            p = strtok(line, " ");
            for (i = 0; i < 12; ++i) {
                if (p == NULL || !strcmp(p, "\n")) {
                    break;
                }
                sscanf(p, "%lf", &float_line[i]);
                p = strtok(NULL, " ");

                if (i == 11) {
                    for (int j = 0; j < 12; ++j) {
                        pointer_of_array[j] = float_line[j];
                    }
                    k += 12;
                    array_of_points = realloc(array_of_points, sizeof(double) * (k + number_of_coordinates_of_cells));
                    pointer_of_array = array_of_points + k;
                }
            }
        }
    }

    total_number_of_points = k;
    number_of_cell = total_number_of_points / number_of_coordinates_of_cells;

    if (PRINT_READ_DATA) {
        print_array_of_points(array_of_points, number_of_cell, number_of_coordinates_of_cells);
    }

    struct_of_points *array_struct = malloc(
            sizeof(double) * total_number_of_points + sizeof(total_number_of_points) + sizeof(number_of_cell));

    array_struct->number_of_cell = number_of_cell;
    array_struct->total_number_of_coordinates = total_number_of_points;
    array_struct->array = array_of_points;
    array_struct->number_of_coordinates_at_point = NUMBER_OF_COORDINATES_AT_POINT;

    return array_struct;
}

/**
 * Получить точки коллокации
 * @param vector_of_points
 * @param number_of_cells
 * @return
 */
double *get_collocation_points(double *vector_of_points, int number_of_cells) {
    double coordinate = 0, initial_coordinate = 0;
    double array_of_collocation_points[number_of_cells][NUMBER_OF_COORDINATES_AT_POINT];

    MACROS_GET_ARRAY_CELL(vector_of_points, number_of_cells)

    double *return_array = malloc(sizeof(double) * number_of_cells * NUMBER_OF_COORDINATES_AT_POINT);
    double *pointer_to_array = return_array;
    for (int i = 0; i < number_of_cells; ++i) {
        for (int j = 0; j < NUMBER_OF_COORDINATES_AT_POINT; ++j) {
            for (int k = 0; k < NUMBER_OF_POINTS_PER_CELL; ++k) {
                coordinate = coordinate + array_of_cell[i][k][j];
            }
            *pointer_to_array = coordinate / 4;
            pointer_to_array++;
            array_of_collocation_points[i][j] = coordinate / 4;
            coordinate = initial_coordinate;
        }
    }

    return return_array;
}


/**
 * Получить векторное произведение двух векторов
 * @param vector_1
 * @param vector_2
 * @return
 */
double *get_vec_multip(double *vector_1, double *vector_2) {
    double *vec_multip = malloc(sizeof(double) * NUMBER_OF_COORDINATES_AT_POINT);
    vec_multip[0] = vector_1[1] * vector_2[2] - vector_1[2] * vector_2[1];
    vec_multip[1] = vector_1[2] * vector_2[0] - vector_1[0] * vector_2[2];
    vec_multip[2] = vector_1[0] * vector_2[1] - vector_1[1] * vector_2[0];
    return vec_multip;
}

/**
 * Получить норму вектора
 * @param vector
 * @return
 */
double get_vector_norma(double *vector){
    return sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
}

/**
 * Для каждой ячейки получить нормаль n и касательные векторы tau1 и tau2
 * @param vector_of_points
 * @param number_of_cells
 * @return
 */
vectors_in_cells *get_array_of_vec(double *vector_of_points, int number_of_cells) {
    vectors_in_cells *vectors = malloc(sizeof(vectors_in_cells));
    double* normal = malloc(sizeof(double) * NUMBER_OF_COORDINATES_AT_POINT * number_of_cells);
    double* tau1 = malloc(sizeof(double) * NUMBER_OF_COORDINATES_AT_POINT * number_of_cells);
    double* tau2 = malloc(sizeof(double) * NUMBER_OF_COORDINATES_AT_POINT * number_of_cells);


    int counter1 = 0, counter2 = 0, counter3 = 0;
    for (int i = 0; i < number_of_cells; ++i) {
        diag *diagonals = get_diag_of_cell(&vector_of_points[counter3]);
        counter3 += NUMBER_OF_COORDINATES_AT_POINT*NUMBER_OF_POINTS_PER_CELL;

        double *vec_multip = get_vec_multip(diagonals->diag1, diagonals->diag2);
        double vec_multip_norma = get_vector_norma(vec_multip);
        double diag1_norma = get_vector_norma(diagonals->diag1);

        normal[counter1] = vec_multip[0] / vec_multip_norma;
        tau1[counter1++] = diagonals->diag1[0]/diag1_norma;

        normal[counter1] = vec_multip[1] / vec_multip_norma;
        tau1[counter1++] = diagonals->diag1[1]/diag1_norma;

        normal[counter1] = vec_multip[2] / vec_multip_norma;
        tau1[counter1++] = diagonals->diag1[2]/diag1_norma;

        vec_multip = get_vec_multip(&normal[counter2], &tau1[counter2]);
        tau2[counter2++] = vec_multip[0];
        tau2[counter2++] = vec_multip[1];
        tau2[counter2++] = vec_multip[2];
    }
    vectors->normals = normal;
    vectors->tau1 = tau1;
    vectors->tau2 = tau2;

    return vectors;
}

/**
 * Получить диагонали ячейки разбиения
 * @param cell
 * @return
 */
diag *get_diag_of_cell(const double *cell) {
    double *diag1 = malloc(sizeof(double) * NUMBER_OF_COORDINATES_AT_POINT);
    double *diag2 = malloc(sizeof(double) * NUMBER_OF_COORDINATES_AT_POINT);
    diag *diagonals = malloc(sizeof(diag));

    int i = 0, j = 0;

    j = (NUMBER_OF_COORDINATES_AT_POINT * NUMBER_OF_POINTS_PER_CELL) / 2;

    diag1[0] = *(cell + i++) - *(cell + j++);
    diag1[1] = *(cell + i++) - *(cell + j++);
    diag1[2] = *(cell + i++) - *(cell + j++);

    diag2[0] = *(cell + i++) - *(cell + j++);
    diag2[1] = *(cell + i++) - *(cell + j++);
    diag2[2] = *(cell + i) - *(cell + j);

    diagonals->diag1 = diag1;
    diagonals->diag2 = diag2;
    return diagonals;
}

/**
 * Получить площадь ячейки
 * @param cell
 * @return
 */
double get_cell_area(double *cell) {
    diag *diagonals = get_diag_of_cell(cell);
    double *diag1 = diagonals->diag1;
    double *diag2 = diagonals->diag2;

    double diag1_length = sqrt(diag1[0] * diag1[0] + diag1[1] * diag1[1] + diag1[2] * diag1[2]);
    double diag2_length = sqrt(diag2[0] * diag2[0] + diag2[1] * diag2[1] + diag2[2] * diag2[2]);
    double scalar_mult_diag1_diag2 = diag1[0] * diag2[0] + diag1[1] * diag2[1] + diag1[2] * diag2[2];
    return diag1_length *
           diag2_length *
           sqrtf(1 - pow((scalar_mult_diag1_diag2 / (diag1_length * diag2_length)), 2)) / 2;
}

/**
 * Получить массив площадей ячеек
 * @param vector_of_points
 * @param number_of_cells
 * @return
 */
double *get_array_of_cell_area(double *vector_of_points, int number_of_cells) {
    double *array_of_cells_area = malloc(sizeof(double) * number_of_cells);
    double *cell = malloc(sizeof(double) * NUMBER_OF_POINTS_PER_CELL * NUMBER_OF_COORDINATES_AT_POINT);
    double areaSum = 0;

    MACROS_GET_ARRAY_CELL(vector_of_points, number_of_cells)

    for (int i = 0; i < number_of_cells; ++i) {
        int counter = 0;
        for (int j = 0; j < NUMBER_OF_POINTS_PER_CELL; ++j) {
            for (int k = 0; k < NUMBER_OF_COORDINATES_AT_POINT; ++k) {
                *(cell + counter++) = array_of_cell[i][j][k];
            }
        }
        array_of_cells_area[i] = get_cell_area(cell);
        areaSum += array_of_cells_area[i];
    }
    return array_of_cells_area;
}
