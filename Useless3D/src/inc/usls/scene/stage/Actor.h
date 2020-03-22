#pragma once

#include <optional>
#include <string>

#include "glm/glm.hpp"

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/stage/transform/Transform.h"

namespace usls
{
    class Actor
    {
    private:
        Transform               transform;
        std::optional<int>      meshIndex;
        std::string             name;
        

    public:
        Actor(std::string name, Transform t);
        Actor(std::string name, Transform t, int meshIndex);

        std::string             getName();
        //void draw(Shader* shader);

    };
}