#include <algorithm>
#include <carrental1_dynamic_program.h>

namespace carrental1 {

DynamicProgram::DynamicProgram(const Params& params)
    : params_(params)
{
    initDistributions();
    initValues();
    initPolicy();
}

void DynamicProgram::run()
{
    while (running_)
    {
        runPolicyEvaluation();
        runPolicyImprovement();
    }
}

void DynamicProgram::initDistributions()
{
    reqDis1_.init(params_.lambdaRequest1_, params_.epsilon_);
    retDis1_.init(params_.lambdaReturn1_, params_.epsilon_);
    reqDis2_.init(params_.lambdaRequest2_, params_.epsilon_);
    retDis2_.init(params_.lambdaReturn2_, params_.epsilon_);
}

void DynamicProgram::initValues()
{
    values_.resize(params_.maxCars1_ + 1);
    for (auto it = values_.begin(); it != values_.end(); ++it)
    {
        it->resize(params_.maxCars2_ + 1);
        std::fill(it->begin(), it->end(), 0.0);
    }
}

void DynamicProgram::initPolicy()
{
    policy_.resize(params_.maxCars1_ + 1);
    for (auto it = values_.begin(); it != values_.end(); ++it)
    {
        it->resize(params_.maxCars2_ + 1);
        std::fill(it->begin(), it->end(), 0.0);
    }
}

void DynamicProgram::runPolicyEvaluation()
{
    double maxDelta, newValue, delta;

    do
    {
        maxDelta = 0.0;
        for (int cars1 = 0; cars1 <= params_.maxCars1_; ++cars1)
        {
            for (int cars2 = 0; cars2 <= params_.maxCars2_; ++cars2)
            {
                newValue = q(cars1, cars2, policy_[cars1][cars2]);
                delta = abs(newValue - values_[cars1][cars2]);
                values_[cars1][cars2] = newValue;
                if (delta > maxDelta)
                {
                    maxDelta = delta;
                }
            }
        }
    } while(maxDelta > params_.epsilon_);
}

void DynamicProgram::runPolicyImprovement()
{
    bool stable = true;

    for (int cars1 = 0; cars1 <= params_.maxCars1_; ++cars1)
    {
        for (int cars2 = 0; cars2 <= params_.maxCars2_; ++cars2)
        {
            int carsMoved = -std::min(cars2, params_.maxCarMoved_);
            int maxAction = std::min(cars1, params_.maxCarMoved_);
            int bestAction = carsMoved;
            double bestValue = q(cars1, cars2, carsMoved);

            for (++carsMoved; carsMoved <= cars1; ++carsMoved)
            {
                double value = q(cars1, cars2, carsMoved);
                if (value > bestValue)
                {
                    bestValue = value;
                    bestAction = carsMoved;
                }
            }

            if (bestAction != policy_[cars1][cars2])
            {
                stable = false;
                policy_[cars1][cars2] = maxAction;
            }
        }
    }

    if (stable)
    {
        running_ = false;
    }
}

double DynamicProgram::q(int cars1, int cars2, int carsMoved)
{
    double cost = abs(carsMoved) * params_.costPerCarMoved_;
    double reward, newValue = 0.0;
    double p1, p2, p3, p4;
    int req1, ret1, req2, ret2;
    int left1, left2, rent1, rent2;
    int newCars1, newCars2;

    left1 = std::min(cars1 - carsMoved, params_.maxCars1_);
    left2 = std::min(cars2 + carsMoved, params_.maxCars2_);

    p1 = reqDis1_(0);
    for (req1 = 0; p1 > params_.epsilon_; p1 = reqDis1_(++req1))
    {
        rent1 = std::min(left1, req1);
        p2 = p1 * retDis1_(0);
        for (ret1 = 0; p2 > params_.epsilon_; p2 = p1 * retDis1_(++ret1))
        {
            newCars1 = std::min(left1 - rent1 + ret1,
                                params_.maxCars1_);
            p3 = p2 * reqDis2_(0);
            for (req2 = 0; p3 > params_.epsilon_; p3 = p2 * reqDis2_(++req2))
            {
                rent2 = std::min(left2, req2);
                reward = (rent1 + rent2) * params_.rewardPerCarRented_;
                p4 = p3 * retDis2_(0);
                for (ret2 = 0; p4 > params_.epsilon_; p4 = p3 * retDis2_(++ret2))
                {
                    newCars2 = std::min(left2 - rent2 + ret2,
                                        params_.maxCars2_);
                    newValue += p4 * (reward - cost +
                                      params_.discount_ * values_[newCars1][newCars2]);
                }
            }
        }
    }

    return newValue;
}

} // end of namespace carrental1
