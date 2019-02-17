/*
 * Размерность матрицы задается на этапе компиляции параметром ключом -DGRID_DIM=10000
 */

#ifndef GRID_DIM
#define GRID_DIM 100
#endif

#include <iostream>
#include <omp.h>
#include "functions.h"

/**
 * Trapezium Area
 */
double trapeziumS(double x1, double x2) {
    return ((f(x2) + f(x1)) / 2) * (x2 - x1);
}

/**
 * Error estimation function
 */
double R(double a, double b, int steps) {
    return (b - a) / (24 * steps * steps) * f_2(max_abs(a, b, steps));
}

/**
 * Whole figure area
 */ 
double S(double a, double b, int steps) {
    double step = (b - a) / steps;
    double result = 0;

    #pragma omp parallel for reduction(+:result)
    for(int i = 0; i < steps; i ++) {
        double x1 = a + step * i;
        double x2 = x1 + step;
        result += trapeziumS(x1, x2);
    }

    return result;
}

int main() {
    std::cout << S(A, B, GRID_DIM) << std::endl;
    std::cout << R(A, B, GRID_DIM) << std::endl;
    return 0;
}
