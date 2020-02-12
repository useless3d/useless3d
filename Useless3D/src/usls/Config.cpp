#include "inc/Config.h"

namespace usls
{
    Config::Config() {};

    Config* Config::instance = 0;

    Config* Config::get()
    {
        if (instance == 0)
        {
            instance = new Config();
        }
        return instance;
    }
}