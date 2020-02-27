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
    public:
        const bool          headless;
        const Config        config;

    private:
                            App(bool headless);
        static App*         instance;

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
        static void         init(bool headless = false);
        static App*         get();
        
        void                setScene(std::unique_ptr<Scene> scene);
        void                clearScene();
        const double        time() const;
        const InputState&   getInputState() const;
        const glm::vec2&    getScreenSize() const;
        void                execute();
        void                close();

    };
};
