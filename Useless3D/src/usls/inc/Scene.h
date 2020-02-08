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
        static std::optional<std::unique_ptr<Stage>>    stage;

    public:
        static void setStage(std::string file);

        Scene();
        ~Scene();
    };
}