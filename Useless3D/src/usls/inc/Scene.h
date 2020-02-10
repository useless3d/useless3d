#pragma once

#include "Stage.h"
#include <optional>
#include <string>
#include <memory>

namespace usls
{
    class Scene
    {
    private:
        std::optional<std::unique_ptr<Stage>> stage;


    public:
        Scene();
        ~Scene();
        void    setStage(std::string file);
        void    draw();
        void    clear();

        
    };
}