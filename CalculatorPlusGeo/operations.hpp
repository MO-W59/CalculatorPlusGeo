/* Header for all the basic math operations. */

#pragma once

#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <vector>

namespace operations
{
    double circleArea(const double&);

    double sphereVol(const double&);

    double triangleArea(const double& a, const double& b, const double& c);

    double triPyVol(const double&, const double&);

    double quadPyVol(const double&, const double&);
}

#endif // OPERATIONS_H