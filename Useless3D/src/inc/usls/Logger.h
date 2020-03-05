#pragma once

#include <string>


namespace usls
{

    class Logger
    {
    private:
        bool                enabled;
        std::string         path;

    public:
                            Logger(bool enabled, std::string path);
        void                log(std::string entry);
    };

}