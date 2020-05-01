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
		glm::mat4		matrix;
	};
}