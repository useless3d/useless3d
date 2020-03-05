#include <fstream>
#include <sstream>

#include "usls/helpers.h"

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

    std::string char_to_string(char* a)
    {
        std::string s = "";
        for (int i = 0; i < (sizeof(a) / sizeof(char)); i++) {
            s = s + a[i];
        }
        return s;
    }

}