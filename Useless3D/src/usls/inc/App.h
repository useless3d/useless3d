#pragma once

#include <glm/glm.hpp>
#include "InputState.h"
#include "Window.h"
#include "Ini.h"
//#include "Scene.h"

namespace usls 
{
    
    class App
    {
    protected:
        Ini             ini;
    public:
        glm::vec2       screenSize;
    protected:
        Window          window;
        double          maxFps;
        double          logicTick;
        double			deltaTime = 0.0;
        double			currentTime = 0.0;
        double			newTime = 0.0;
        double			frameTime = 0.0;
        double			accumulator = 0.0;
        //Scene           scene;

    public:       
        InputState      input;
        App(Ini ini);
        ~App();
        virtual void    logicLoop() = 0;
        virtual void    init() = 0;
        void            execute();

    };

};
