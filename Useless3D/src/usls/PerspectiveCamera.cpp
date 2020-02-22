#include "inc/PerspectiveCamera.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace usls
{
    PerspectiveCamera::PerspectiveCamera(const glm::vec2* screenSize, bool fixed, float nearPlane, float farPlane, float fov) :
        fov(fov),
        Camera(screenSize, fixed, nearPlane, farPlane)
    {

    }

    void PerspectiveCamera::updateProjectionMatrix()
    {
        this->projectionMatrix = glm::perspective(glm::radians(this->fov),
            (float)this->screenSize->x / (float)this->screenSize->y, this->nearPlane, this->farPlane);

        //std::cout << glm::to_string(this->projectionMatrix) << "\n";
    }

}