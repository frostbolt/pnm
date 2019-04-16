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


namespace D2
{
    namespace Rectangle
    {
        double S(double posize_t, double step);
        double R(double a, double b, double c, double d, size_t n);
    }

    namespace LeftRectangle
    {
        using namespace Rectangle;
        double solve(double a, double b, double c, double d, size_t n);
    }

    namespace RightRectangle
    {
        using namespace Rectangle;
        double solve(double a, double b, double c, double d, size_t n);
    }

    namespace MidRectangle
    {
        using Rectangle::S;

        double R(double a, double b, double c, double d, size_t n);
        double solve(double a, double b, double c, double d, size_t n);
    }

    namespace Trapezium
    {
        double S(double x1, double x2);
        double R(double a, double b, double c, double d, size_t n);
        double solve(double a, double b, double c, double d, size_t n);
    }

    namespace Simpson
    {
        double R(double a, double b, double c, double d, size_t n);
        double solve(double a, double b, double c, double d, size_t n);
    }

    namespace ThreeEights
    {
        double R(double a, double b, double c, double d, size_t n);
        double solve(double a, double b, double c, double d, size_t n);
    }

    namespace MonteCarlo
    {
        double R(double a, double b, double c, double d, size_t n);
        double solve(double a, double b, double c, double d, size_t n);
    }
}


#endif // __RECTANGLES_H__