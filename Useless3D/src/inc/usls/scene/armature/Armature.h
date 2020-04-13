#pragma once

#include <string>
#include <vector>

#include "usls/scene/armature/Bone.h"


namespace usls::scene::armature
{
	class Armature
	{
	private:
		std::string name;
		size_t animationIndex;
		std::vector<Bone> bones;

		

	public:
		Armature(std::string name);

		void addBone(Bone b);

		std::vector<Bone>& getBones();

		size_t getBoneIndex(std::string boneName);

	};
}