#pragma once

#include <string>
#include <vector>
#include <optional>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"


namespace usls::scene::armature
{
	struct Bone
	{
		std::string		name;
		std::string		parentName;
		size_t			parent;

		glm::vec3		translation;
		glm::quat		rotation;
		glm::vec3		scale;
		glm::mat4		matrix; // always the matrix of current translation/rotation/scale

		// used to interpolate render state
		glm::vec3		previousTranslation;
		glm::quat		previousRotation;
		glm::vec3		previousScale;
	};
}