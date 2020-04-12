#pragma once

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "usls/scene/stage/Transform.h"

namespace usls::scene::armature
{
	struct Bone
	{
		std::string						name;
		std::string						parent;
		usls::scene::stage::Transform	currentTransform;
	};
}