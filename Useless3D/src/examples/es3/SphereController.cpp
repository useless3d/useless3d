#include <iostream>

#include "usls/App.h"
#include "examples/es3/SphereController.h"



SphereController::SphereController(Actor* sphere) :
	actor(sphere),
	direction(glm::vec3(0.0f, 0.0f, -1.0f)),
	speed(2.5f),
	usls::scene::stage::Controller() 
{};

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
	this->actor->translate(this->actor->getTranslation() + this->velocity);

}

