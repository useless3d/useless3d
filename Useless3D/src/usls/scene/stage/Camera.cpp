#include <iostream>


#include "usls/App.h"
#include "usls/scene/stage/Camera.h"



namespace usls
{
    Camera::Camera(CameraType type, bool fixed, float nearPlane, float farPlane, float fovScale) :
        type(type),
        screenSize(&App::get().getScreenSize()),
        fixed(fixed),
        nearPlane(nearPlane),
        farPlane(farPlane),
        fovScale(fovScale)
    {
        
    }

    void Camera::updateViewMatrix()
    {
        if (!this->fixed) {
            this->viewMatrix = glm::lookAt(this->position, this->lookAt, this->up);
        }
    }

    void Camera::update()
    {
        this->updateViewMatrix();
        this->updateProjectionMatrix();
    }

    glm::mat4 Camera::getViewMatrix()
    {
        return this->viewMatrix;
    }

    glm::mat4 Camera::getProjectionMatrix()
    {
        return this->projectionMatrix;
    }

    void Camera::setPosition(float x, float y, float z)
    {
        this->position = glm::vec3(x, y, z);
    }

    void Camera::setLookAt(float x, float y, float z)
    {
        this->lookAt = glm::vec3(x, y, z);
    }

    glm::vec3 Camera::getPosition()
    {
        return this->position;
    }

    void Camera::updateProjectionMatrix()
    {
        if (type == CameraType::ORTHOGRAPHIC) 
        {
            float aspect = (float)this->screenSize->x / (float)this->screenSize->y;
            float sizeX = fovScale * aspect;
            float sizeY = fovScale;
            this->projectionMatrix = glm::ortho(-sizeX, sizeX, -sizeY, sizeY, this->nearPlane, this->farPlane);
        }
        else
        {
            this->projectionMatrix = glm::perspective(glm::radians(this->fovScale),
                (float)this->screenSize->x / (float)this->screenSize->y, this->nearPlane, this->farPlane);
        }

    }

}