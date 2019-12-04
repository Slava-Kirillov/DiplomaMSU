#ifndef DIPLOMAMSU_COMPUTATION_SERVICE_H
#define DIPLOMAMSU_COMPUTATION_SERVICE_H

#include <complex.h>

#pragma STDC CX_LIMITED_RANGE on

// заголовочный файл определяет функции для расчета интеграла по ячейке I = S f(x, e, k, y) d sigma, где
// d sigma - площать элементарной ячейки

float integrand_function(float *x, float eps, complex float k, float *y);

float (*integrand_function_pointer)(float *x, float eps, complex float k, float *y);

float cell_integral(float *x,
                    int m,
                    int n,
                    float eps,
                    complex float k,
                    float (*integrand_function)(float *x, float eps, complex float k, float *y));

#endif
