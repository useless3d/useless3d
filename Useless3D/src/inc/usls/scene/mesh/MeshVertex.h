#pragma once

#include "glm/glm.hpp"

namespace usls
{
    struct MeshVertex 
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 textureCoordinates;

        bool operator==(const MeshVertex &) const;

    };    
}