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

double const A1 = 0;
double const B1 = 2;
double const C1 = 0;
double const D1 = 2;

inline double fn(long double x, long double y) {
	return x*y+y*y;
}

inline double fn_x(long double x, long double y) {
	return y;
}

inline double fn_y(long double x, long double y) {
	return 1 - 2*y;
}

inline double fn_xx(long double x, long double y) {
	return 0;
}

inline double fn_yy(long double x, long double y) {
	return -2;
}

inline double fn_xy(long double x, long double y){
	return 1;
}

#endif //__CONDITION_H__