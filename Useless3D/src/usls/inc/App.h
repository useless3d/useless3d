#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <vector>

#include "Config.h"
#include "Window.h"
#include "Stage.h"


namespace usls 
{
    class App
    {
    protected:

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
        void                addStage(std::string stageName, std::string filePath, ProjectionType projType, ViewSpace vSpace);

        const InputState&   getInputState() const;

        virtual void        perFrameLogic() = 0;
        virtual void        init() = 0;
        

    public:
        App();
        ~App();
        void                execute();

    };
};
