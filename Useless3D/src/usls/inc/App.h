#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <vector>

#include "Config.h"
#include "Window.h"
#include "Stage.h"
#include "Camera.h"


namespace usls 
{
    class App
    {
    protected:
        bool                headless;
        Config              config;
        Window              window;
        double              maxFps;
        double              logicTick = 120.0;
        double			    deltaTime = 0.0;
        double			    currentTime = 0.0;
        double			    newTime = 0.0;
        double			    frameTime = 0.0;
        double			    accumulator = 0.0;

        std::vector<Stage>  stages;
        void                addStage(std::string stageName, std::unique_ptr<Camera> camera);
        void                addStage(std::string stageName);

        const InputState&   getInputState() const;

        virtual void        perFrameLogic() = 0;
        virtual void        init() = 0;
        

    public:
        App(bool headless);
        ~App();
        void                execute();

        //const Window&       getWindow();

    };
};
