#include "inc/Logger.h"

namespace usls
{
    bool Logger::enabled;
    std::string Logger::path;
    std::ofstream Logger::fs;

    Logger::Logger() {};
    Logger::~Logger() {};

    void Logger::enable(std::string path) 
    {
        Logger::enabled = true;
        Logger::path = path;
    }

    bool Logger::isEnabled()
    {
        return Logger::enabled;
    }

    void Logger::log(std::string message)
    {
        Logger::fs.open(path, std::ios_base::app);
        Logger::fs << message << "\n";
        Logger::fs.close();
    }

    std::string Logger::charToString(char* a)
    {
        std::string s = "";
        for (int i = 0; i < (sizeof(a) / sizeof(char)); i++) {
            s = s + a[i];
        }
        return s;
    }

}