#pragma once

namespace usls
{
    struct Ini
    {
        int         screenWidth = 1280;
        int         screenHeight = 720;
        bool        fullScreen = false;
        int         maxFps = 500;
        int         logicTick = 120;
    };
}