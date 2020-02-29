#include "inc/Logger.h"

#include <fstream>

namespace usls
{

    Logger::Logger(bool enabled, std::string path) :
        enabled(enabled),
        path(path)
    {
        
    };

    void Logger::log(std::string message)
    {
        if (this->enabled)
        {
            std::ofstream fs;
            fs.open(this->path, std::ios_base::app);
            fs << message << "\n";
            fs.close();
        }
    }

    

}