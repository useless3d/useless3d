#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "usls/scene/stage/Controller.h"
#include "usls/scene/stage/Camera.h"


class CameraController : public usls::scene::stage::Controller
{
private:
	usls::scene::stage::Camera*		camera;
	glm::vec3						moveDirection;
	glm::vec3						lookDirection;
	glm::vec3						up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3						velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	float							moveSpeed;

	bool							firstMouseInput = true;
	float							lastX;
	float							lastY;
	size_t							mouseDeltaBufferSize;
	size_t							mouseDeltaBufferCursor = 0;
	std::vector<float>				mouseDeltaBufferX;
	std::vector<float>				mouseDeltaBufferY;

	float							yaw;
	float							pitch;

	void							updateRotation();
	void							updatePitchYaw();
	void							updateVelocity();

public:
									CameraController(usls::scene::stage::Camera* camera);
	void							logic();
};