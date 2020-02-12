#pragma once

#include <string>

namespace usls
{
    /*
        This will eventually have functionality for reading and writing values to and from
        an .ini file
    */
    class Config
    {
    private:
        Config();
        static Config* instance;

    public:
        static Config* get();

        bool        logEnabled = true;
        std::string logPath = "data/log.txt";
        int         screenWidth = 1280;
        int         screenHeight = 720;
        bool        fullScreen = false;
        int         maxFps = 500;
        int         logicTick = 120;

    };
}