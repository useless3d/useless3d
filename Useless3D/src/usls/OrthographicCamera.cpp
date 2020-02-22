#include "inc/OrthographicCamera.h"
#include <glm/gtx/string_cast.hpp>

#include <iostream>

namespace usls
{
    OrthographicCamera::OrthographicCamera(const glm::vec2* screenSize, bool fixed, float nearPlane, float farPlane) :
        Camera(screenSize, fixed, nearPlane, farPlane)
    {

    }

    void OrthographicCamera::updateProjectionMatrix()
    {
        //this->projectionMatrix = glm::mat4(1.0f);

        float width = (float)this->screenSize->x / 100;
        float height = (float)this->screenSize->y / 100;

        //float width = 6.0f;
        //float height = 4.0f;

        this->projectionMatrix = glm::ortho(-(width / 2.0f), (width / 2.0f), 
            -(height / 2.0f), (height / 2.0f), this->nearPlane, this->farPlane);
        
        //this->projectionMatrix = glm::ortho(0.0f, (float)this->screenSize->x, (float)this->screenSize->y,
        //    0.0f, this->nearPlane, this->farPlane);

        //std::cout << glm::to_string(this->projectionMatrix) << "\n";
    }

}