#ifndef INCLUDED_COMMON_JSON_PARAM_H
#define INCLUDED_COMMON_JSON_PARAM_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <initializer_list>
#include <rapidjson/document.h>
#include <common_exception.h>
#include <common_string_utils.h>
#include <common_validator.h>
#include <common_json_utils.h>
#include <common_parse.h>

namespace common {

class JsonParam {
public:
    JsonParam(const std::vector<std::string>& path,
              bool required=true) noexcept;

    virtual void parse(const rapidjson::Value& doc) = 0;

protected:
    std::vector<std::string> path_;
    bool required_;
};

using JsonParamPtr = std::shared_ptr<JsonParam>;

template <typename T>
class TypedJsonParam: public JsonParam {
public:
    TypedJsonParam(T& var,
                   const std::vector<std::string>& path,
                   bool required=true,
                   const Validator<T>& v=Validator<T>()) noexcept;

    void parse(const rapidjson::Value& doc) override;

protected:
    T& var_;
    Validator<T> validator_;
};

template <typename T>
TypedJsonParam<T>::TypedJsonParam(T& var,
                                  const std::vector<std::string>& path,
                                  bool required,
                                  const Validator<T>& v) noexcept
    : JsonParam(path, required)
    , var_(var)
    , validator_(v)
{
}

template <typename T>
JsonParamPtr jsonParam(T& var,
                       const std::vector<std::string>& path,
                       bool required=true,
                       Validator<T> v=Validator<T>())
{
    return JsonParamPtr(new TypedJsonParam<T>(var, path, required, v));
}

template <typename T>
JsonParamPtr jsonParam(T& var,
                       std::initializer_list<std::string> path,
                       bool required=true,
                       Validator<T> v=Validator<T>())
{
    return jsonParam(var, std::vector<std::string>(path), required, v);
}

template <typename T>
JsonParamPtr jsonParam(T& var,
                       const std::string& name,
                       bool required=true,
                       Validator<T> v=Validator<T>())
{
    return JsonParamPtr(new TypedJsonParam<T>(var, {name}, required, v));
}

template <typename T>
void TypedJsonParam<T>::parse(const rapidjson::Value& value)
{
    const rapidjson::Value* v = findJson(value, path_);
    if (!v)
    {
        if (required_)
        {
            THROW_EXCEPT(ParseException,
                         "Failed to find path " + stringVal(path_));
        }

        return;
    }

    common::parse(var_, *v);

    if (!validator_.validate(var_))
    {
        THROW_EXCEPT(ParseException,
                     "Validation failed for " + stringVal(path_) +
                     ": " + validator_.description(var_));
    }
}

void parse(std::vector<JsonParamPtr>& params,
           const rapidjson::Value& v);

} // end of namespace common

#endif
