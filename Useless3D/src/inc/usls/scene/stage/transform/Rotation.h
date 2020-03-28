#pragma once

#include "glm/glm.hpp"

namespace usls
{
    struct Rotation 
    {
        float		angle = 0.0f;
        glm::vec3	axis = glm::vec3(0.1f, 0.1f, 0.1f); // must be initialized with non 0.0f to generate mvp, doesn't matter as angle is 0.0f
    };
}