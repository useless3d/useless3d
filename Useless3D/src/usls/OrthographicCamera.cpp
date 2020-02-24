#include "inc/OrthographicCamera.h"
#include <glm/gtx/string_cast.hpp>

#include <iostream>

namespace usls
{
    OrthographicCamera::OrthographicCamera(const glm::vec2* screenSize, bool fixed, float nearPlane, float farPlane, float pixelsPerUnit) :
        pixelsPerUnit(pixelsPerUnit),
        Camera(screenSize, fixed, nearPlane, farPlane)
    {

    }

    void OrthographicCamera::updateProjectionMatrix()
    {
        float z = 1.0f;
        float fov = 45.0f;
        float ratioSizePerDepth = atan(glm::radians(fov / 2.0f) * 2.0f);
        float aspect = (float)this->screenSize->x / (float)this->screenSize->y;
        float sizeX = ratioSizePerDepth * z * aspect;
        float sizeY = ratioSizePerDepth * z;

        this->projectionMatrix = glm::ortho(-sizeX, sizeX, -sizeY, sizeY, this->nearPlane, this->farPlane);


        //float width = (float)this->screenSize->x / this->pixelsPerUnit;
        //float height = (float)this->screenSize->y / this->pixelsPerUnit;

        //this->projectionMatrix = glm::ortho(-(width / 2.0f), (width / 2.0f), 
        //    -(height / 2.0f), (height / 2.0f), this->nearPlane, this->farPlane);


    }

}