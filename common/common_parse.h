#ifndef INCLUDED_COMMON_PARSE_H
#define INCLUDED_COMMON_PARSE_H

#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <rapidjson/document.h>
#include <common_exception.h>

namespace common {

inline void parse(std::string &str,
                  const std::string &s)
{
    str = s;
}

inline void parse(int &i,
                  const std::string &s)
{
    i = std::stoi(s);
}

inline void parse(long &l,
                  const std::string &s)
{
    l = std::stol(s);
}

inline void parse(long long &l,
                  const std::string &s)
{
    l = std::stoll(s);
}

inline void parse(float &f,
                  const std::string &s)
{
    f = std::stof(s);
}

inline void parse(double &d,
                  const std::string &s)
{
    d = std::stod(s);
}

inline void parse(long double &d,
                  const std::string &s)
{
    d = std::stold(s);
}

void parse(bool& b,
           const rapidjson::Value& v);

void parse(int& i,
           const rapidjson::Value& v);

void parse(unsigned int& u,
           const rapidjson::Value& v);

void parse(int64_t& i,
           const rapidjson::Value& v);

void parse(uint64_t& u,
           const rapidjson::Value& v);

void parse(float& f,
           const rapidjson::Value& v);

void parse(double& d,
           const rapidjson::Value& v);

void parse(std::string& s,
           const rapidjson::Value& v);

template <typename T>
void parse(std::vector<T>& a,
           const rapidjson::Value& v)
{
    if (!v.IsArray())
    {
        THROW_EXCEPT(ParseException, "Json object is not an array");
    }

    a.resize(v.Capacity());
    for (std::size_t i = 0; i < a.size(); ++i)
    {
        parse(a[i], v[i]);
    }
}

template <typename T, std::size_t N>
void parse(std::array<T,N>& a,
           const rapidjson::Value& v)
{
    if (!v.IsArray())
    {
        THROW_EXCEPT(ParseException, "Json object is not an array");
    }

    std::size_t sz = std::min(N, static_cast<std::size_t>(v.Capacity()));
    for (std::size_t i = 0; i < sz; ++i)
    {
        parse(a[i], v[i]);
    }
}

} // end of namespace common

#endif

