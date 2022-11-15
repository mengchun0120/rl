#include <common_json_utils.h>
#include <common_json_param.h>
#include <carrental1_params.h>

using namespace common;

namespace carrental1 {

Params::Params(const std::string& paramFile)
{
    rapidjson::Document doc;
    readJson(doc, paramFile);

    std::vector<JsonParamPtr> params{
        jsonParam(maxCars1_, "maxCars1", true, gt(0)),
        jsonParam(maxCars2_, "maxCars2", true, gt(0)),
        jsonParam(maxCarMoved_, "maxCarMoved", true, gt(0)),
        jsonParam(rewardPerCarRented_, "rewardPerCarRented", true, gt(0.0)),
        jsonParam(costPerCarMoved_, "costPerCarMoved", true, gt(0.0)),
        jsonParam(discount_, "discount", true, gt(0.0) && le(1.0)),
        jsonParam(epsilon_, "epsilon", true, gt(0.0) && lt(1.0)),
        jsonParam(lambdaRequest1_, "lambdaRequest1", true, gt(0.0)),
        jsonParam(lambdaReturn1_, "lambdaReturn1", true, gt(0.0)),
        jsonParam(lambdaRequest2_, "lambdaRequest2", true, gt(0.0)),
        jsonParam(lambdaReturn2_, "lambdaReturn2", true, gt(0.0))
    };

    parse(params, doc);
}

} // end of namespace carrental1
