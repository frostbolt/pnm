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
double Trapezium::R(double a, double b, size_t steps) {
    return (b - a) / (24 * steps * steps) * f_2(max_abs(a, b, steps));
}

/**
 * Whole figure area using Trapezium method
 */
Solution Trapezium::solve(double a, double b, size_t steps) {
    auto startTime = std::chrono::steady_clock::now();
    double step = (b - a) / steps;
    double result = 0;

    #pragma omp parallel for reduction(+:result)
    for (size_t i = 0; i < steps; i++) {
        double x1 = a + step * i;
        double x2 = x1 + step;
        result += S(x1, x2);
    }

    auto mulTime = std::chrono::steady_clock::now();
    auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);

    return Solution(omp_get_max_threads(), result, R(a, b, steps), runtimeDuration.count());
}


/**
 * Rectangle Area
 */
double Rectangle::S(double point, double step) { 
    // TODO: Get rid of this.
    return f(point) * step;
}

/**
 * Error estimation function
 */
double Rectangle::R(double a, double b, size_t steps) {
    return (b - a) / (24 * steps * steps) * f_2(max_abs(a, b, steps));
}

/**
 * Whole figure area using Left Rectangle method
 */
Solution LeftRectangle::solve(double a, double b, size_t steps) {
    auto startTime = std::chrono::steady_clock::now();
    double step = (b - a) / steps;
    double result = 0;

    #pragma omp parallel for reduction(+:result)
    for (size_t i = 0; i < steps; i++) {
        double x1 = a + step * i;
        result += S(x1, step);
    }

    auto mulTime = std::chrono::steady_clock::now();
    auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);

    return Solution(omp_get_max_threads(), result, R(a, b, steps), runtimeDuration.count());
}

/**
 * Whole figure area using Right Rectangle method
 */
Solution RightRectangle::solve(double a, double b, size_t steps) {
    auto startTime = std::chrono::steady_clock::now();
    double step = (b - a) / steps;
    double result = 0;

    #pragma omp parallel for reduction(+:result)
    for (size_t i = 0; i < steps; i++) {
        double x2 = a + step * (i + 1);
        result += S(x2, step);
    }

    auto mulTime = std::chrono::steady_clock::now();
    auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);

    return Solution(omp_get_max_threads(), result, R(a, b, steps), runtimeDuration.count());
}

/**
 * Whole figure area using Middle Rectangle method
 */
Solution MidRectangle::solve(double a, double b, size_t steps) {
    auto startTime = std::chrono::steady_clock::now();
    double step = (b - a) / steps;
    double result = 0;

    #pragma omp parallel for reduction(+:result)
    for (size_t i = 0; i < steps; i++) {
        double x1 = a + step * (i + 0.5);
        result += S(x1, step);
    }

    auto mulTime = std::chrono::steady_clock::now();
    auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);

    return Solution(omp_get_max_threads(), result, R(a, b, steps), runtimeDuration.count());
}
