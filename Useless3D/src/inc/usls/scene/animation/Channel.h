#pragma once

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"



namespace usls::scene::animation
{
	struct Channel
	{
		std::string name;
		std::vector<std::pair<double, glm::vec3>> positionKeys;
		std::vector<std::pair<double, glm::quat>> rotationKeys;
		std::vector<std::pair<double, glm::vec3>> scalingKeys;
	};	
}