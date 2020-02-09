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
        std::optional<std::unique_ptr<Stage>>    stage;

    public:
        void setStage(std::string file);
        Stage* getStage();
        void draw();

        Scene();
        ~Scene();
    };
}