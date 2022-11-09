#ifndef INCLUDED_CARRENTAL1_PARAMS_H
#define INCLUDED_CARRENTAL1_PARAMS_H

namespace carrental1 {

struct Params {
    int maxCars1_;
    int maxCars2_;
    int maxCarMoved_;
    double rewardPerCarRented_;
    double costPerCarMoved_;
    double discount_;
    double epsilon_;
    double lambdaRequest1_;
    double lambdaReturn1_;
    double lambdaRequest2_;
    double lambdaReturn2_;
};


} // end of namespace carrental1

#endif
