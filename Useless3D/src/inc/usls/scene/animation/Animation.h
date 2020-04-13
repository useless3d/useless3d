#pragma once

#include <vector>
#include <string>

#include "usls/scene/animation/Channel.h"

namespace usls::scene::animation
{
	struct Animation
	{
		std::string				name;
		double					duration;
		double					tps;
		std::vector<Channel>	channels;
	};
	
}