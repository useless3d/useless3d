#pragma once

#include "glm/glm.hpp"

#include "usls/scene/stage/Controller.h"
#include "usls/scene/stage/Actor.h"


class ActorController : public usls::scene::stage::Controller
{
private:
	Actor*		actor;
	glm::vec3	direction;
	glm::vec3	up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	float		speed;

	float		yaw;
	float		pitch;

	void		updateRotation();
	void		updateVelocity();

public:
				ActorController(Actor* sphere);
	void		logic();
};