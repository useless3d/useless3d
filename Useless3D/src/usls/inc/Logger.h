#pragma once

#include <string>
#include <fstream>

namespace usls
{

    class Logger
    {
    private:
        Logger();
        ~Logger();
        static bool             enabled;
        static std::string      path;
        static std::ofstream    fs;
    public:
        static void             enable(std::string path);
        static bool             isEnabled();
        static void             log(std::string entry);
        static std::string      charToString(char* a);
    };

}