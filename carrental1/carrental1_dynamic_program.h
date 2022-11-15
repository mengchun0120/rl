#ifndef INCLUDED_CARRENTAL1_DYNAMIC_PROGRAM_H
#define INCLUDED_CARRENTAL1_DYNAMIC_PROGRAM_H

#include <vector>
#include <common_poisson_distribution.h>
#include <carrental1_params.h>
#include <carrental1_typedef.h>

namespace carrental1 {

class DynamicProgram {
public:
    DynamicProgram(const Params& params);

    void run();

    inline const ValueTable& values() const;

    inline const ActionTable& policy() const;

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
    ValueTable values_;
    ActionTable policy_;
    bool running_;
};

const ValueTable& DynamicProgram::values() const
{
    return values_;
}

const ActionTable& DynamicProgram::policy() const
{
    return policy_;
}

} // end of namespace carrental1

#endif
