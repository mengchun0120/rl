#ifndef INCLUDED_CARRENTAL1_POISSON_DISTRIBUTION_H
#define INCLUDED_CARRENTAL1_POISSON_DISTRIBUTION_H

#include <vector>

namespace carrental1 {

class PoissonDistribution {
public:
    PoissonDistribution() = default;

    PoissonDistribution(double lambda, double epsilon);

    void init(double lambda, double epsilon);

    inline double operator()(int k) const;

    inline int max() const;

private:
    std::vector<double> distr_;
};

double PoissonDistribution::operator()(int k) const
{
    return distr_[k];
}

int PoissonDistribution::max() const
{
    return static_cast<int>(distr_.size()) - 1;
}

} // end of namespace carrental1

#endif
