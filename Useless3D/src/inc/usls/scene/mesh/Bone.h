#pragma once

#include <vector>

#include "glm/glm.hpp"

namespace usls::scene::mesh
{
	struct Bone
	{
		std::string name;
		glm::mat4 offsetMatrix;
		std::vector<std::pair<size_t, float>> vertexWeights;
	};
}