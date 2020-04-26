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
		std::string										name;
		std::string										parentName;
		std::vector<std::string>						childNames;
		size_t											parent; // index of parent in containing armature
		std::vector<size_t>								children; // indexes of children in containing armature
		glm::mat4										matrix;
	};
}