#pragma once

#include <vector>
#include <string>

#include "usls/scene/armature/Bone.h"

namespace usls::scene::armature
{
	struct Animation
	{
		std::string			name;
		double				duration;
		double				tps;
		std::vector<Bone>	bones;
	};
	
}