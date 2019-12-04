#include "headers/computation_service.h"

float integrand_function(float *x, float eps, complex float k, float *y) {

    float result;

    return result;
}

float cell_integral(float *x,
                    int m,
                    int n,
                    float eps,
                    complex float k,
                    float (*integrand_function)(float *x, float eps, complex float k, float *y)) {

    float *y;
    float cell_integral_result = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            float s;
            float integrand_function_result = integrand_function(x, eps, k, y);
            cell_integral_result += integrand_function_result * s;
        }
    }

    return cell_integral_result;
}

void test() {
    float x[] = {1, 2, 3};
    int m = 2, n = 2;
    float eps = 1.5f;
    complex float k =  3.1 + I*4.2;

    integrand_function_pointer = integrand_function;

    float cell_internal_result = cell_integral(x, m, n, eps, k, integrand_function_pointer);
}