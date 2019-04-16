#include <omp.h>
#include <chrono>
#include <stdexcept>
#include <random>

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



/**
 * Double integral using LeftRectangle methods
 */
double D2::LeftRectangle::solve(double a, double b, double c, double d, size_t n) {
    double h_x = (b - a) / n;
    double h_y = (d - c) / n;
    double sum = 0;
    #pragma omp parallel for schedule(static) reduction(+ : sum)
    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - 1; j++)
        {
            double x = a + h_x * i;
            double y = c + h_y * j;
            sum += fn(x, y);
        }
    return h_x * h_y * sum;
}

/**
 * Double integral using RightRectangle methods
 */
double D2::RightRectangle::solve(double a, double b, double c, double d, size_t n) {
    double h_x = (b - a) / n;
    double h_y = (d - c) / n;
    double sum = 0;
    #pragma omp parallel for schedule(static) reduction(+ : sum)
    for (size_t i = 1; i < n; i++)
        for (size_t j = 1; j < n; j++)
        {
            double x = a + h_x * i;
            double y = c + h_y * j;
            sum += fn(x, y);
        }
    return h_x * h_y * sum;
}

/**
 * Double integral using MidRectangle methods
 */
double D2::MidRectangle::solve(double a, double b, double c, double d, size_t n) {
    double h_x = (b - a) / n;
    double h_y = (d - c) / n;
    double sum = 0;
    #pragma omp parallel for schedule(static) reduction(+ : sum)
    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - 1; j++)
        {
            double x = a + h_x * i + h_x / 2;
            double y = c + h_y * j + h_y / 2;
            sum += fn(x, y);
        }

    return h_x * h_y * sum;
}

/**
 * Double integral using Trapezium methods
 */
double D2::Trapezium::solve(double a, double b, double c, double d, size_t n) {
    double h_x = (b - a) / n;
    double h_y = (d - c) / n;
    double sum = 0;

    #pragma omp parallel for schedule(static) reduction(+ : sum)
    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - 1; j++)
        {
            double x0 = a + h_x * i;
            double x1 = a + h_x * (i + 1);

            double y0 = c + h_y * j;
            double y1 = c + h_y * (j + 1);

            sum += fn(x0, y0) + fn(x1, y1);
        }

    return h_x * h_y * sum / 2;
}

/**
 * Double integral using Simpson methods
 */
double D2::Simpson::solve(double a, double b, double c, double d, size_t n) {
    double h_x = (b - a) / n;
    double h_y = (d - c) / n;
    double sum = 0;

    #pragma omp parallel for schedule(static) reduction(+ : sum)
    for (size_t i = 0; i < n - 1; i += 2)
        for (size_t j = 0; j < n - 1; j += 2)
        {
            double x0 = a + h_x * i;
            double x1 = a + h_x * (i + 1);
            double x2 = a + h_x * (i + 2);

            double y0 = c + h_y * j;
            double y1 = c + h_y * (j + 1);
            double y2 = c + h_y * (j + 2);

            sum += fn(x0, y0) + 4 * fn(x1, y0) + fn(x2, y0) +
                   4 * (fn(x0, y1) + 4 * fn(x1, y1) + fn(x2, y1)) +
                   fn(x0, y2) + 4 * fn(x1, y2) + fn(x2, y2);
        }

    return h_x * h_y * sum / 9;
}

/**
 * Double integral using ThreeEights methods
 */
double D2::ThreeEights::solve(double a, double b, double c, double d, size_t n) {
    double h_x = (b - a) / n;
    double h_y = (d - c) / n;
    double sum = 0;

    #pragma omp parallel for schedule(static) reduction(+ : sum)
    for (size_t i = 0; i < n - 1; i += 3)
        for (size_t j = 0; j < n - 1; j += 3)
        {
            double x0 = a + h_x * i;
            double x1 = a + h_x * (i + 1);
            double x2 = a + h_x * (i + 2);
            double x3 = a + h_x * (i + 3);

            double y0 = c + h_y * j;
            double y1 = c + h_y * (j + 1);
            double y2 = c + h_y * (j + 2);
            double y3 = c + h_y * (j + 3);

            sum += fn(x0, y0) + 3 * fn(x1, y0) + 3 * fn(x2, y0) + fn(x3, y0) +
                   3 * (fn(x0, y1) + 3 * fn(x1, y1) + 3 * fn(x2, y1) + fn(x3, y1)) +
                   3 * (fn(x0, y2) + 3 * fn(x1, y2) + 3 * fn(x2, y2) + fn(x3, y2)) +
                   fn(x0, y3) + 3 * fn(x1, y3) + 3 * fn(x2, y3) + fn(x3, y3);
        }

    return 3. / 8 * 3. / 8 * h_x * h_y * sum;
}

/**
 * Double integral using MonteCarlo methods
 */
double D2::MonteCarlo::solve(double a, double b, double c, double d, size_t n) {
    std::random_device randD;
    std::mt19937 randMT(randD());
    std::uniform_real_distribution<> rand_x(a, b);
    std::uniform_real_distribution<> rand_y(c, d);

    double S = 0.0;
    #pragma omp parallel for reduction(+ : S)
    for (int i = 0; i < n; i++) 
        S += fn(rand_x(randMT), rand_y(randMT));

    return ((b - a) * (d - c)) / n * S;
}

/**
 * Error estimation function for D2::MidRectangle
 */
double D2::Rectangle::R(double a, double b, double c, double d, size_t n)  {
    return fabs(D2::MidRectangle::solve(a, b, c, d, n) - D2::MidRectangle::solve(a, b, c, d, 2*n));
}
/**
 * Error estimation function for D2::MidRectangle
 */
double D2::MidRectangle::R(double a, double b, double c, double d, size_t n)  {
    return fabs(D2::MidRectangle::solve(a, b, c, d, n) - D2::MidRectangle::solve(a, b, c, d, 2*n));
}

/**
 * Error estimation function for D2::ThreeEights
 */
double D2::ThreeEights::R(double a, double b, double c, double d, size_t n)  {
    return fabs(D2::ThreeEights::solve(a, b, c, d, n) - D2::ThreeEights::solve(a, b, c, d, 2*n));
}

/**
 * Error estimation function for D2::Trapezium
 */
double D2::Trapezium::R(double a, double b, double c, double d, size_t n)  {
    return fabs(D2::Trapezium::solve(a, b, c, d, n) - D2::Trapezium::solve(a, b, c, d, 2*n));
}

/**
 * Error estimation function for D2::Simpson
 */
double D2::Simpson::R(double a, double b, double c, double d, size_t n)  {
    return fabs(D2::Simpson::solve(a, b, c, d, n) - D2::Simpson::solve(a, b, c, d, 2*n));
}

/**
 * Error estimation function forD2::MonteCarlo
 */
double D2::MonteCarlo::R(double a, double b, double c, double d, size_t n)  {
    return fabs(D2::MonteCarlo::solve(a, b, c, d, n) - D2::MonteCarlo::solve(a, b, c, d, 2*n));
}



