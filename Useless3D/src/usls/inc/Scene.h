#pragma once

#include "Stage.h"
#include "Camera.h"
#include <string>
#include <vector>
#include <map>
#include "Shader.h"


namespace usls
{
    class Scene
    {
    private:
        Scene();
        static Scene* instance;
        
        std::map<std::string, Stage*> stages;       

        Shader              shader; // default shader, everything renderd using this for now, will consider multiple shaders down the road once this solidifies more

    public:
        static Scene*       get();
        
        int                 getStageCount();
        int                 getStagePropCount(std::string sName);
        
        void                addStage(std::string name, std::string file, ProjectionType pType, ViewSpace vSpace);
        void                clearStages();

        int                 getTotalMeshCount();

        void                draw();
        void                clear();

        
    };
}