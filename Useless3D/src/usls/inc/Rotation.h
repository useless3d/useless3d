#pragma once

#include <glm/glm.hpp>

namespace usls
{
    struct Rotation 
    {

        float		angle = 0.0f;
        glm::vec3	axis = glm::vec3(0.1f, 0.1f, 0.1f); // has to be set to something to generate mvp, doesn't matter as angle is 0.0f

    };
}