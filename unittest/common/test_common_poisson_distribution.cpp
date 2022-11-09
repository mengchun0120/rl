#include <cassert>
#include <cmath>
#include <iostream>
#include <common_math_utils.h>
#include <common_poisson_distribution.h>

using namespace common;

void testPoissonDistribution()
{
    double lambda = 2.0, epsilon = 1e-7;
    PoissonDistribution d(lambda, epsilon);

    assert(fuzzyEqual(d(0), exp(-lambda)));
    assert(fuzzyEqual(d(1), lambda * exp(-lambda)));
    assert(fuzzyEqual(d(2), lambda * lambda * exp(-lambda) / 2.0));
    assert(fuzzyEqual(d(3), lambda * lambda * lambda * exp(-lambda) / 6.0));
    assert(d(d.max()) > epsilon);

    std::cout << "testPoissonDistribution finished" << std::endl;
}
