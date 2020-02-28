#include "inc/helpers.h"

#include <fstream>
#include <sstream>

namespace usls
{
    std::vector<std::string> explode_string(std::string const & s, char delim)
    {
        std::vector<std::string> result;
        std::istringstream iss(s);

        for (std::string token; std::getline(iss, token, delim); )
        {
            result.push_back(std::move(token));
        }

        return result;
    }
}