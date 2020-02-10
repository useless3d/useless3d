#pragma once

#include <string>

namespace usls
{
    struct Config
    {
        bool        logEnabled = true;
        std::string logPath = "data/log.txt";
        int         screenWidth = 1280;
        int         screenHeight = 720;
        bool        fullScreen = false;
        int         maxFps = 500;
        int         logicTick = 120;
    };
}