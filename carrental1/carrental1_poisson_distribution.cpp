#include <cmath>
#include <list>
#include <algorithm>
#include <carrental1_poisson_distribution.h>

namespace carrental1 {

PoissonDistribution::PoissonDistribution(double lambda, double epsilon)
{
    init(lambda, epsilon);
}

void PoissonDistribution::init(double lambda, double epsilon)
{
    std::list<double> probs;
    double cur = exp(-lambda);
    double k = 0.0;

    do
    {
        probs.push_back(cur);
        k += 1.0;
        cur = cur * lambda / k;
    }
    while (cur > epsilon);

    distr_.resize(probs.size());
    std::copy(probs.begin(), probs.end(), distr_.begin());
}

} // end of namespace carrental1
