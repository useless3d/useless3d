

#include "glm/gtx/string_cast.hpp"

#include "usls/scene/camera/PerspectiveCamera.h"


namespace usls
{
    PerspectiveCamera::PerspectiveCamera(bool fixed, float nearPlane, float farPlane, float fov) :
        fov(fov),
        Camera(fixed, nearPlane, farPlane){}

    void PerspectiveCamera::updateProjectionMatrix()
    {
        this->projectionMatrix = glm::perspective(glm::radians(this->fov),
            (float)this->screenSize->x / (float)this->screenSize->y, this->nearPlane, this->farPlane);
    }

}