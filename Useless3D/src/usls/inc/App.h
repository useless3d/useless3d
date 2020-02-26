#pragma once

#include <memory>
#include <vector>
#include <optional>

#include "Config.h"
#include "Window.h"
#include "Scene.h"


namespace usls 
{
    class App
    {
    private:
        bool                shouldClose = false;
        Window              window;
        std::optional<std::unique_ptr<Scene>> scene;
        const double        maxFps;
        const double        logicTick = 120.0;
        double			    deltaTime = 0.0;
        double			    currentTime = 0.0;
        double			    newTime = 0.0;
        double			    frameTime = 0.0;
        double			    accumulator = 0.0;        

    public:
        App(bool headless);

        const bool          headless;
        const Config        config;
        
        void                setScene(std::unique_ptr<Scene> scene);
        void                clearScene();
        const double        time() const;
        const InputState&   getInputState() const;
        void                execute();
        void                close();

    };
};
