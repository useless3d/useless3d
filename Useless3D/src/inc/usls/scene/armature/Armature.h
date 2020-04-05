#pragma once

#include <string>
#include <vector>

#include "usls/scene/armature/Animation.h"

namespace usls::scene::armature
{
	class Armature
	{
	private:
		std::string name;
		std::vector<Animation> animations;

	public:
		Armature(std::string name);

	};
}