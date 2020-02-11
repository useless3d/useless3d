#pragma once

#include "Stage.h"
#include <optional>
#include <string>
#include <memory>
#include "Mesh.h"

namespace usls
{
    class Scene
    {
    private:
        std::vector<std::shared_ptr<Mesh>> meshes;
        std::optional<std::unique_ptr<Stage>> stage;


    public:
        Scene();
        ~Scene();
        void    setStage(std::string file);
        void    draw();
        void    clear();

        
    };
}