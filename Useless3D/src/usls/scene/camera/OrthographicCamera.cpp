

#include "glm/gtx/string_cast.hpp"

#include "usls/scene/camera/OrthographicCamera.h"


namespace usls
{
    OrthographicCamera::OrthographicCamera(bool fixed, float nearPlane, float farPlane, float scale = 1.0f) :
        scale(scale),
        Camera(fixed, nearPlane, farPlane){}

    void OrthographicCamera::updateProjectionMatrix()
    {
        float aspect = (float)this->screenSize->x / (float)this->screenSize->y;
        float sizeX = scale * aspect;
        float sizeY = scale;
        this->projectionMatrix = glm::ortho(-sizeX, sizeX, -sizeY, sizeY, this->nearPlane, this->farPlane);
    }

}