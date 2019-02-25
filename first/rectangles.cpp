/*
 * Grid dimension can be specified with a specific compilers flag. Eg: -DGRID_DIM=10000
 */

#ifndef GRID_DIM
#define GRID_DIM 100
#endif

#include <omp.h>
#include <chrono>
#include <stdexcept>

#include "functions.h"

#include "rectangles.h"

/**
 * Trapezium Area
 */
double Trapezium::S(double x1, double x2) {
    return ((f(x2) + f(x1)) / 2) * (x2 - x1);
}

/**
 * Error estimation function
 */
double Trapezium::R(double a, double b, int steps) {
    return (b - a) / (24 * steps * steps) * f_2(max_abs(a, b, steps));
}

/**
 * Whole figure area using Trapezium method
 */
Solution Trapezium::solve(double a, double b, int steps) {
    auto startTime = std::chrono::steady_clock::now();
    double step = (b - a) / steps;
    double result = 0;

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < steps; i ++) {
        double x1 = a + step * i;
        double x2 = x1 + step;
        result += trapeziumS(x1, x2);
    }

    auto mulTime = std::chrono::steady_clock::now();
    auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);

    return Solution(result, runtimeDuration);
}


/**
 * Rectangle Area
 */
double Rectangle::S(double point, double step) {
    return f(point) * step;
}

/**
 * Error estimation function
 */
double Rectangle::R(double a, double b, int steps) {
    return (b - a) / (24 * steps * steps) * f_2(max_abs(a, b, steps));
}

/**
 * Whole figure area using Left Rectangle method
 */
Solution LeftRectangle::solve(double a, double b, int steps) {
    auto startTime = std::chrono::steady_clock::now();
    double step = (b - a) / steps;
    double result = 0;

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < steps; i ++) {
        double x1 = a + step * i;
        result += S(x1, step);
    }

    auto mulTime = std::chrono::steady_clock::now();
    auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);

    return Solution(result, runtimeDuration);
}