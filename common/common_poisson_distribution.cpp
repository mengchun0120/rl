#include <cmath>
#include <common_poisson_distribution.h>

namespace common {

PoissonDistribution::PoissonDistribution(double lambda, double epsilon)
{
    init(lambda, epsilon);
}

void PoissonDistribution::init(double lambda, double epsilon)
{
    double cur = exp(-lambda);
    double k = 0.0;

    do
    {
        distr_.push_back(cur);
        k += 1.0;
        cur = cur * lambda / k;
    }
    while (cur > epsilon);
}

} // end of namespace common
