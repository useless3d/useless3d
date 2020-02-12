#pragma once

#include "Stage.h"
#include <optional>
#include <string>


namespace usls
{
    class Scene
    {
    private:
        Scene();
        static Scene* instance;
        
        std::optional<Stage*> stage;
        


    public:
        static Scene*   get();
        
        int             getStagePropCount();
        void            setStage(std::string file);
        void            clearStage();

        int             getTotalMeshCount();

        void            draw();
        void            clear();

        
    };
}