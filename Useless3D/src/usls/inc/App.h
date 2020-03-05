#pragma once

#include <memory>
#include <vector>
#include <optional>
#include <chrono>

#include "Config.h"
#include "Logger.h"
#include "Window.h"
#include "Scene.h"


namespace usls 
{
    // https://stackoverflow.com/a/1008289/1609485
    class App
    {
    public:
        const Config        config;
        Logger              logger;

    private:
                            App();
        Window              window;
        std::chrono::high_resolution_clock::time_point startTime;

        bool                shouldClose = false;
        double			    deltaTime = 0.0;
        double			    currentTime = 0.0;
        double			    newTime = 0.0;
        double			    frameTime = 0.0;
        double			    accumulator = 0.0;        

        std::optional<std::unique_ptr<Scene>> scene;
    
    public:
        static App&         get();
        static void         init();

                            App(App const&) = delete;
        void                operator=(App const&) = delete;

        void                setScene(std::unique_ptr<Scene> scene);
        void                clearScene();
        const double        time() const;
        const InputState&   getInputState() const;
        const glm::vec2&    getScreenSize() const;
        void                execute();
        void                close();

    };
};
