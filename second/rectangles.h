#ifndef __RECTANGLES_H__
#define __RECTANGLES_H__

#include "Solution.h"

namespace Rectangle
{
    double S(double posize_t, double step);
    double R(double a, double b, size_t steps);
}


namespace LeftRectangle
{
    using namespace Rectangle;
    Solution solve(double a, double b, size_t steps);
}

namespace RightRectangle
{
    using namespace Rectangle;
    Solution solve(double a, double b, size_t steps);
}

namespace MidRectangle
{
    using Rectangle::S;

    double R(double a, double b, size_t steps);
    Solution solve(double a, double b, size_t steps);
}

namespace Trapezium
{
    double S(double x1, double x2);
    double R(double a, double b, size_t steps);
    Solution solve(double a, double b, size_t steps);
}

namespace Simpson
{
    double R(double a, double b, size_t steps);
    Solution solve(double a, double b, size_t steps);
}

namespace ThreeEights
{
    double R(double a, double b, size_t steps);
    Solution solve(double a, double b, size_t steps);
}


#endif // __RECTANGLES_H__