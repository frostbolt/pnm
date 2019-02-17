#include "functions.h"

double max_abs(double a, double b, double steps) {
    double step = (b - a) / steps;
    double result = 0;

    while (a < b) {
        if (result <= f(a))
            result = f(a);
        a += step;
    }

    return result;
}