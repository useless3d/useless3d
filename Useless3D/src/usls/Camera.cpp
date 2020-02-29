#include "inc/Camera.h"

#include "inc/App.h"

namespace usls
{
    Camera::Camera(bool fixed, float nearPlane, float farPlane) :
        screenSize(&App::get().getScreenSize()),
        fixed(fixed),
        nearPlane(nearPlane),
        farPlane(farPlane)
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

    void Camera::setPosition(glm::vec3 p)
    {
        this->position = p;
    }

    void Camera::setLookAt(glm::vec3 la)
    {
        this->lookAt = la;
    }

}