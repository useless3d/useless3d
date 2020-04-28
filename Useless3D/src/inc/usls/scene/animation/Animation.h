#pragma once

#include <unordered_map>
#include <string>

#include "usls/scene/animation/Channel.h"

namespace usls::scene::animation
{
	struct Animation
	{
		std::string				name;
		double					duration;
		double					tps;
		std::unordered_map<std::string, Channel> channels;
	};
	
}