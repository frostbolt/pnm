#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "cmath"

double const A = 0.1;
double const B = 0.5;

inline double f(double x) {
    return x / (sin(2 * x) * sin(2 * x) * sin(2 * x));
}

inline double cotan(double a) { return 1 / tan(a); }

inline double cosec(double a) { return 1 / sin(a); }

/*
 * Second derivative
 */
inline double f_2(double x) {
    return 12 * pow(cosec(2 * x), 3) * (3 * x * pow(cotan(2 * x), 2) - cotan(2 * x) + x * pow(cosec(2 * x), 2));
}

#endif //__CONDITION_H__