#include "inc/PerspectiveCamera.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "inc/App.h"

namespace usls
{
    PerspectiveCamera::PerspectiveCamera(bool fixed, float nearPlane, float farPlane, float fov) :
        fov(fov),
        Camera(fixed, nearPlane, farPlane)
    {

    }

    void PerspectiveCamera::updateProjectionMatrix()
    {
        this->projectionMatrix = glm::perspective(glm::radians(this->fov),
            (float)this->screenSize->x / (float)this->screenSize->y, this->nearPlane, this->farPlane);

        //std::cout << glm::to_string(this->projectionMatrix) << "\n";
    }

}