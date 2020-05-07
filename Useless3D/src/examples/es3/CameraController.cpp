#include <iostream>


#include "examples/es3/CameraController.h"



CameraController::CameraController(usls::scene::stage::Camera* camera) :
	camera(camera),
	moveDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
	lookDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
	speed(4.0f),
	yaw(0.0f),
	//pitch(-20.45f),
	pitch(0.0f),
	usls::scene::stage::Controller()
{};

void CameraController::updateRotation()
{
	this->updatePitchYaw();

	// rotate movement direction
	this->moveDirection.x = cos(glm::radians(this->yaw));
	this->moveDirection.y = 0.0f;
	this->moveDirection.z = sin(glm::radians(this->yaw));
	this->moveDirection = glm::normalize(this->moveDirection);

	// rotate view direction
	this->lookDirection.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->lookDirection.y = sin(glm::radians(this->pitch));
	this->lookDirection.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->lookDirection = glm::normalize(this->lookDirection);
}

void CameraController::updateVelocity()
{
	float currentSpeed = this->speed * this->deltaTime;

	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	if (this->input.keyW)
		this->velocity += currentSpeed * this->moveDirection;
	if (this->input.keyS)
		this->velocity -= currentSpeed * this->moveDirection;
	if (this->input.keyA)
		this->velocity -= glm::normalize(glm::cross(this->moveDirection, this->up)) * currentSpeed;
	if (this->input.keyD)
		this->velocity += glm::normalize(glm::cross(this->moveDirection, this->up)) * currentSpeed;

}

void CameraController::updatePitchYaw()
{
	if (this->firstMouseInput)
	{
		this->lastX = this->input.mouseXPos;
		this->lastY = this->input.mouseYPos;
		this->firstMouseInput = false;
	}

	float xOffset = this->input.mouseXPos - this->lastX;
	float yOffset = this->lastY - this->input.mouseYPos;

	this->lastX = this->input.mouseXPos;
	this->lastY = this->input.mouseYPos;

	float sensitivity = 0.1f; // change accordingly
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	this->yaw += xOffset;
	this->pitch += yOffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;
}

void CameraController::logic()
{
	this->updateVelocity();
	this->updateRotation();

	// update camera
	auto newPosition = this->camera->getPosition() + this->velocity;
	this->camera->setPosition(newPosition);
	this->camera->setLookAt(newPosition + this->lookDirection);

}

