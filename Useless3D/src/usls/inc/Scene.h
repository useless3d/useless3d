#pragma once

#include "Stage.h"
#include "Camera.h"
#include <string>
#include <vector>
#include <map>


namespace usls
{
    class Scene
    {
    private:
        Scene();
        static Scene* instance;
        
        std::map<std::string, Stage*> stages;

        std::vector<Prop>   getStageProps(std::string sName);
        


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