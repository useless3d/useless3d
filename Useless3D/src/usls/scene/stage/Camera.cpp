#include <iostream>

#define GLM_FORCE_ALIGNED_GENTYPES
#include "glm/gtx/matrix_decompose.hpp"

#include "usls/App.h"
#include "usls/scene/stage/Camera.h"



namespace usls::scene::stage
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

	void Camera::updatePreviousTransform()
	{
		this->previousTransform = this->currentTransform;
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

    void Camera::updateViewMatrix(float alpha)
    {
        if (!this->fixed) {

            this->viewMatrix = glm::lookAt(this->position, this->lookAt, this->up);

			glm::vec3 scale;
			glm::quat rotation;
			glm::vec3 translation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(this->viewMatrix, scale, rotation, translation, skew, perspective);
			rotation = glm::conjugate(rotation);

			this->currentTransform.setTranslation(translation);
			this->currentTransform.setRotation(rotation);
			this->currentTransform.setScale(scale);

			this->viewRenderMatrix = Transform::interpolateTransforms(this->previousTransform, this->currentTransform, alpha);

        }
    }

    void Camera::update(float alpha)
    {
        this->updateViewMatrix(alpha);
        this->updateProjectionMatrix();
    }

    glm::mat4 Camera::getViewMatrix()
    {
        //return this->viewMatrix;
		return this->viewRenderMatrix;
    }

    glm::mat4 Camera::getProjectionMatrix()
    {
        return this->projectionMatrix;
    }

    void Camera::setPosition(float x, float y, float z)
    {
        this->position = glm::vec3(x, y, z);
    }

	void Camera::setPosition(glm::vec3 position)
	{
		this->position = position;
	}

    void Camera::setLookAt(float x, float y, float z)
    {
        this->lookAt = glm::vec3(x, y, z);
    }

	void Camera::setLookAt(glm::vec3 direction)
	{
		this->lookAt = direction;
	}

    glm::vec3 Camera::getPosition()
    {
        return this->position;
    }

    

}