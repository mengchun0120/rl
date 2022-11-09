#ifndef INCLUDED_COMMON_POISSON_DISTRIBUTION_H
#define INCLUDED_COMMON_POISSON_DISTRIBUTION_H

#include <vector>

namespace common {

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

} // end of namespace common

#endif
