#include "inc/Camera.h"

namespace usls
{
    Camera::Camera(glm::vec2* screenSize) :
        screenSize(screenSize)
    {

    };

    Camera* Camera::instance = 0;

    Camera* Camera::get()
    {
        return instance;
    }

    Camera* Camera::init(glm::vec2* screenSize)
    {
        if (instance == 0)
        {
            instance = new Camera(screenSize);
        }
        return instance;
    }

    void Camera::update()
    {
        this->updateViewMatrix();
        this->updatePerspectiveProjectionMatrix();
    }

    void Camera::setFov(float fov)
    {
        this->fov = fov;
    }

    float Camera::getFov()
    {
        return this->fov;
    }
    
    void Camera::setDirection(glm::vec3 direction) 
    {
        this->direction = direction;
    }

    void Camera::setPosition(glm::vec3 position) 
    {
        this->position = position;
    }

    glm::vec3 Camera::getDirection()
    {
        return this->direction;
    }

    glm::vec3 Camera::getPosition()
    {
        return this->position;
    }

    glm::mat4 Camera::getViewMatrix()
    {
        return this->viewMatrix;
    }

    glm::mat4 Camera::getPerspectiveProjectionMatrix()
    {
        return this->perspectiveProjectionMatrix;
    }

    void Camera::updateViewMatrix() 
    {
        //this->viewMatrix = glm::lookAt(this->position, this->position + this->direction, this->up);
        this->viewMatrix = glm::lookAt(this->position, this->direction, this->up);
    }

    void Camera::updatePerspectiveProjectionMatrix() 
    {
        this->perspectiveProjectionMatrix = glm::perspective(glm::radians(this->fov),
            (float)this->screenSize->x / (float)this->screenSize->y, 0.1f, 500.0f);
    }

}