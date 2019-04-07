#include <omp.h>
#include <chrono>
#include <stdexcept>

#include "functions.h"

#include "rectangles.h"

/**
 * Rectangle Area
 */
double Rectangle::S(double point, double step) { 
    // TODO: Get rid of this.
    return f(point) * step;
}

/**
 * Rectangle Error estimation function
 */
double Rectangle::R(double a, double b, size_t steps) {
    return std::pow(b - a, 2) / (2 * steps) * f_2(max_abs(a, b, steps));
}

/**
 * Areas
 */
double Trapezium::S(double x1, double x2) {
    return ((f(x2) + f(x1)) / 2) * (x2 - x1);
}

/**
 * Error estimation functions
 */
double Trapezium::R(double a, double b, size_t steps) {
    return (b - a) / (24 * steps * steps) * f_2(max_abs(a, b, steps));
}

double MidRectangle::R(double a, double b, size_t steps) {
    return std::pow(b - a, 3) / (24 * steps * steps) * f_2(max_abs(a, b, steps));
}

double Simpson::R(double a, double b, size_t steps) {
    return std::pow(b - a, 5) / (2880 * std::pow(steps, 4)) * f_2(max_abs(a, b, steps));
}

double ThreeEights::R(double a, double b, size_t steps) {
    return std::pow(b - a, 5) / (80 * std::pow(steps, 4)) * f_2(max_abs(a, b, steps));
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

    return Solution(omp_get_max_threads(), result, steps, R(a, b, steps), runtimeDuration.count());
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

    return Solution(omp_get_max_threads(), result, steps, R(a, b, steps), runtimeDuration.count());
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

    return Solution(omp_get_max_threads(), result, steps, R(a, b, steps), runtimeDuration.count());
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

    return Solution(omp_get_max_threads(), result, steps, R(a, b, steps), runtimeDuration.count());
}

/**
 * Whole figure area using Simpson method
 */
Solution Simpson::solve(double a, double b, size_t steps) {
    auto startTime = std::chrono::steady_clock::now();
    double step = (b - a) / steps;
    double result = 0;

    #pragma omp parallel for reduction(+:result)
    for (size_t i = 0; i < steps; i+= 2) {
        double x0 = a + step * i;
        double x1 = a + step * (i + 1);
        double x2 = a + step * (i + 2);
        result += f(x0) + 4 * f(x1) + f(x2);
    }

    result = step / 3 * result;

    auto mulTime = std::chrono::steady_clock::now();
    auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);

    return Solution(omp_get_max_threads(), result, steps, R(a, b, steps), runtimeDuration.count());
}


/**
 * Whole figure area using Simpson method
 */
Solution ThreeEights::solve(double a, double b, size_t steps) {
    auto startTime = std::chrono::steady_clock::now();
    double step = (b - a) / steps;
    double result = 0;

    #pragma omp parallel for reduction(+:result)
    for (size_t i = 0; i < steps; i+= 3) {
        double x0 = a + step * i;
        double x1 = a + step * (i + 1);
        double x2 = a + step * (i + 2);
        double x3 = a + step * (i + 3);
        result += f(x0) + 3 * (f(x1) + f(x2)) + f(x3);
    }

    result = 3. / 8 * step * result;

    auto mulTime = std::chrono::steady_clock::now();
    auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);

    return Solution(omp_get_max_threads(), result, steps, R(a, b, steps), runtimeDuration.count());
}