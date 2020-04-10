#pragma once

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "usls/scene/transform/Transform.h"

using namespace usls::scene::transform;

namespace usls::scene::armature
{
	struct Bone
	{
		std::string		name;
		std::string		parent;
		Transform		currentTransform;
	};
}