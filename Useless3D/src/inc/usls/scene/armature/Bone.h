#pragma once

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"



namespace usls::scene::armature
{
	struct Bone
	{
		std::string name;
		std::vector<glm::vec3> positions;
		std::vector<glm::quat> rotations;
		std::vector<glm::vec3> scalings;
	};	
}