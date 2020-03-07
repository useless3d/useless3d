#pragma once

#include <vector>
#include <string>
#include <optional>

#include "usls/scene/Actor.h"

namespace usls
{
    class Stage
    {
    private:
        std::vector<Actor*>    actors;
        std::optional<std::string> cameraName;

    public:
        Stage();
        Stage(std::string cameraName);

    };
}