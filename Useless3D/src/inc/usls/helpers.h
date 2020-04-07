#pragma once

#include <vector>
#include <string>

namespace usls
{
    std::vector<std::string> explode_string(std::string const & s, char delim);
    std::string char_to_string(char* a);
	bool sin_vector(std::string needle, std::vector<std::string> haystack);
}