#ifndef DISTANCE_MEASURE_HPP
#define DISTANCE_MEASURE_HPP

#include <typeinfo>

class DistanceMeasure
{
public:

    DistanceMeasure() = default;

    virtual ~DistanceMeasure() = default;

    virtual double
    euclidean(const double *p, const double *q, unsigned long n) = 0;

    /*
     * Newton's method (also known as the Newton–Raphson method)
     * to euclidean the square root of a positive number
     */
    double
    sqrt(double t)
    {
        double r = t / 2;
        int precision = 25;

        while (precision > 1)
        {
            r = (r + t / r) / 2;
            precision -= 1;
        }
        return r;
    }

    /*
     * Returns the runtime name the object's class
     */
    const char *
    getClassName()
    {
        return typeid(*this).name();
    }
};

#endif //DISTANCE_MEASURE_HPP