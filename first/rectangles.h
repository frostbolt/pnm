#ifndef __RECTANGLES_H__
#define __RECTANGLES_H__

#include "Solution.h"

namespace Trapezium
{
    double S(double x1, double x2);
    double R(double a, double b, int steps);
    Solution solve(double a, double b, int steps);
}

namespace Rectangle
{
    double S(double point, double step);
    double R(double a, double b, int steps);
}

namespace LeftRectangle
{
    using namespace Rectangle;

    Solution solve(double a, double b, int steps);
}

#endif // __RECTANGLES_H__