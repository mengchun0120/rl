#ifndef INCLUDED_CARRENTAL1_DYNAMIC_PROGRAM_H
#define INCLUDED_CARRENTAL1_DYNAMIC_PROGRAM_H

#include <vector>
#include <common_poisson_distribution.h>
#include <carrental1_params.h>

namespace carrental1 {

class DynamicProgram {
public:
    DynamicProgram(const Params& params);

    void run();

private:
    void initDistributions();

    void initValues();

    void initPolicy();

    void runPolicyEvaluation();

    void runPolicyImprovement();

    double q(int cars1, int cars2, int carsMoved);

private:
    const Params& params_;
    common::PoissonDistribution reqDis1_, retDis1_;
    common::PoissonDistribution reqDis2_, retDis2_;
    std::vector<std::vector<double>> values_;
    std::vector<std::vector<int>> policy_;
    bool running_;
};

} // end of namespace carrental1

#endif
