#ifndef INCLUDED_CARRENTAL1_UTILS_H
#define INCLUDED_CARRENTAL1_UTILS_H

#include <fstream>
#include <vector>
#include <common_exception.h>

namespace carrental1 {

template <typename T>
void writeTable(const std::string& file,
                const std::vector<std::vector<T>>& table)
{
    using namespace common;

    std::ofstream os(file);

    if (!os.good())
    {
        THROW_EXCEPT(MyException, "Failed to open file " + file);
    }

    for (unsigned int i = 0; i < table.size(); ++i)
    {
        auto& row = table[i];
        unsigned int rowSize = row.size();

        for (unsigned int j = 0; j < rowSize; ++j)
        {
            os << i << ' ' << j << ' ' << row[j] << std::endl;
        }
    }

    os.close();

}

} // end of namespace carrental1

#endif
