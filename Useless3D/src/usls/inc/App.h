#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "InputState.h"
#include "Window.h"
#include "Config.h"
#include "Scene.h"
#include "Config.h"

namespace usls 
{
    class App
    {
    protected:
        Config          config;
        Window          window;
        double          maxFps;
        double          logicTick = 120.0;
        double			deltaTime = 0.0;
        double			currentTime = 0.0;
        double			newTime = 0.0;
        double			frameTime = 0.0;
        double			accumulator = 0.0;

        const InputState& getInputState() const;

        virtual void    logicLoop() = 0;
        virtual void    init() = 0;
        void            execute();

    public:
        App();
        ~App();
        

    };
};
