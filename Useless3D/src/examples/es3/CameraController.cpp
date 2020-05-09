#include <iostream>
#include <numeric>


#include "examples/es3/CameraController.h"



CameraController::CameraController(usls::scene::stage::Camera* camera) :
	camera(camera),
	moveDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
	lookDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
	moveSpeed(4.0f),
	mouseDeltaBufferSize(3),
	yaw(0.0f),
	pitch(0.0f),
	usls::scene::stage::Controller()
{
	// fill mouse delta buffers
	for (size_t i = 0; i < this->mouseDeltaBufferSize; i++)
	{
		this->mouseDeltaBufferX.push_back(0.0f);
		this->mouseDeltaBufferY.push_back(0.0f);
	}

};

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
	float currentSpeed = this->moveSpeed * this->deltaTime;

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

void CameraController::updatePitchYawRaw()
{
	float sensitivity = 0.2f; // change accordingly

	this->yaw += ((this->input.mouseXPos - this->lastX)) * sensitivity;
	this->pitch += ((this->lastY - this->input.mouseYPos)) * sensitivity;

	this->lastX = this->input.mouseXPos;
	this->lastY = this->input.mouseYPos;
}

void CameraController::updatePitchYawSmoothed()
{
	float sensitivity = 0.08f; // change accordingly

	float xOffset = (this->input.mouseXPos - this->lastX) * sensitivity;
	float yOffset = (this->lastY - this->input.mouseYPos) * sensitivity;

	this->lastX = this->input.mouseXPos;
	this->lastY = this->input.mouseYPos;


	this->mouseDeltaBufferX[this->mouseDeltaBufferCursor] = xOffset / this->deltaTime;
	this->mouseDeltaBufferY[this->mouseDeltaBufferCursor] = yOffset / this->deltaTime;

	this->mouseDeltaBufferCursor = this->mouseDeltaBufferCursor == (this->mouseDeltaBufferSize - 1) ? 0 : this->mouseDeltaBufferCursor + 1;


	this->yaw += (std::accumulate(this->mouseDeltaBufferX.begin(), this->mouseDeltaBufferX.end(), 0.0f) / (float)this->mouseDeltaBufferSize) * this->deltaTime;
	this->pitch += (std::accumulate(this->mouseDeltaBufferY.begin(), this->mouseDeltaBufferY.end(), 0.0f) / (float)this->mouseDeltaBufferSize) * this->deltaTime;
}

void CameraController::updatePitchYawKeyboard()
{
	float currentSpeed = (this->moveSpeed * 16) * this->deltaTime;

	if (this->input.keyUp)
		this->pitch += currentSpeed;
	if (this->input.keyDown)
		this->pitch -= currentSpeed;
	if (this->input.keyLeft)
		this->yaw -= currentSpeed;
	if (this->input.keyRight)
		this->yaw += currentSpeed;
}

void CameraController::updatePitchYaw()
{
	if (this->firstMouseInput)
	{
		this->lastX = this->input.mouseXPos;
		this->lastY = this->input.mouseYPos;
		this->firstMouseInput = false;
	}


	this->updatePitchYawRaw();

	//this->updatePitchYawSmoothed();

	//this->updatePitchYawKeyboard();


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

