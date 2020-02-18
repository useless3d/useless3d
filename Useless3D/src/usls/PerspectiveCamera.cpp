#include "inc/PerspectiveCamera.h"

namespace usls
{
    PerspectiveCamera::PerspectiveCamera(const glm::vec2* screenSize, Projection projectionType,
        ViewSpace viewSpace, float nearPlane, float farPlane, float fov) :
        fov(fov),
        Camera(screenSize, projectionType, viewSpace, nearPlane, farPlane)
    {

    }

    PerspectiveCamera::~PerspectiveCamera() 
    {
        
    }

    void PerspectiveCamera::updateProjectionMatrix()
    {
        this->projectionMatrix = glm::perspective(glm::radians(this->fov),
            (float)this->screenSize->x / (float)this->screenSize->y, this->nearPlane, this->farPlane);
    }

}