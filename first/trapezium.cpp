/*
 * Размерность матрицы задается на этапе компиляции параметром ключом -DGRID_DIM=10000
 */

#ifndef GRID_DIM
#define GRID_DIM 100
#endif

#include <iostream>
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
double R(double a, double b, double steps) {
    return (b - a) / (24 * steps * steps) * f_2(max_abs(a, b, steps));
}

/**
 * Whole figure area
 */ 
double S(double a, double b, double steps) {
    double step = (b - a) / steps;
    double result = 0;

    while (a < b) {
        result += trapeziumS(a, a + step);
        a += step;
    }

    return result;
}

int main() {
    std::cout << S(A, B, GRID_DIM) << std::endl;
    std::cout << R(A, B, GRID_DIM) << std::endl;
    return 0;
}
