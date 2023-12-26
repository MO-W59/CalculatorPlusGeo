/* All math basic functions used for geometry */

#include "operations.hpp"
#include <cmath>

const double PI = 3.1415926535897932384626433832795;

double operations::circleArea(const double& r)
{
    return PI * (pow(r, 2));
}

double operations::triangleArea(const double &a, const double &b, const double &c)
{
    return 0.25 * sqrt((a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c));
}

double operations::sphereVol(const double& r)
{
    return (4.0 / 3.0) * PI * (pow(r, 3));
}

double operations::triPyVol(const double& height, const double& base)
{
    return sqrt(3) / 12 * pow(base, 2) * height;
}

double operations::quadPyVol(const double& height, const double& base)
{
    return 1.0 / 3.0 * pow(base, 2) * height;
}