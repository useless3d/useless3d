#pragma once

#include <memory>
#include <vector>
#include <string>

#include "App.h"
#include "Stage.h"
#include "Shader.h"
#include "Camera.h"


namespace usls 
{

    class Scene
    {
    protected:
        App* const          app;
        Shader              shader;
        std::vector<std::unique_ptr<Stage>>  stages;

        void                addStage(std::string stageName, std::unique_ptr<Camera> camera);
        void                addStage(std::string stageName);

        

    public:
        bool                loaded = false;

                            Scene(App* const app);
        void                draw();         

        virtual void        load() = 0;
        virtual void        loop() = 0;
        

    };

}