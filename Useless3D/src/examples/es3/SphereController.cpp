#include <iostream>

#include "usls/App.h"
#include "examples/es3/SphereController.h"



SphereController::SphereController(Actor* sphere) :
	actor(sphere),
	direction(glm::vec3(0.0f, 0.0f, -1.0f)),
	speed(2.5f),
	yaw(0.0f),
	pitch(-20.45f),
	usls::scene::stage::Controller() 
{};

void SphereController::updateRotation()
{
	//std::cout << this->input.mouseXPos << " - " << this->input.mouseYPos << "\n";

	float currentSpeed = this->speed * this->deltaTime;

	if (this->input.keyUp)
		this->pitch += currentSpeed;
	if (this->input.keyDown)
		this->pitch -= currentSpeed;
	if (this->input.keyLeft)
		this->yaw -= currentSpeed;
	if (this->input.keyRight)
		this->yaw += currentSpeed;

	//if (this->pitch > 89.0f)
	//	this->pitch = 89.0f;
	//if (this->pitch < -89.0f)
	//	this->pitch = -89.0f;

	//std::cout << this->pitch << " - " << this->yaw << "\n";


	this->actor->rotate(glm::quat(glm::vec3(pitch, yaw, 0.0f)));

}

void SphereController::updateVelocity()
{
	float currentSpeed = this->speed * this->deltaTime;

	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	if (this->input.keyW)
		this->velocity += currentSpeed * this->direction;
	if (this->input.keyS)
		this->velocity -= currentSpeed * this->direction;
	if (this->input.keyA)
		this->velocity -= glm::normalize(glm::cross(this->direction, this->up)) * currentSpeed;
	if (this->input.keyD)
		this->velocity += glm::normalize(glm::cross(this->direction, this->up)) * currentSpeed;

}

void SphereController::logic()
{
	this->updateVelocity();
	this->updateRotation();

	this->actor->translate(this->actor->getTranslation() + this->velocity);

}

