#ifndef INCLUDED_COMMON_MATH_UTILS_H
#define INCLUDED_COMMON_MATH_UTILS_H

#include <cmath>

namespace common {

inline bool fuzzyEqual(double a,
                       double b,
                       double threshold=1e-10)
{
    return fabs(a-b) <= threshold;
}

} // end of namespace common

#endif
