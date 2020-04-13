#pragma once

#include <vector>
#include <string>

#include "usls/scene/armature/animation/Channel.h"

namespace usls::scene::armature::animation
{
	struct Animation
	{
		std::string				name;
		double					duration;
		double					tps;
		std::vector<Channel>	channels;
	};
	
}