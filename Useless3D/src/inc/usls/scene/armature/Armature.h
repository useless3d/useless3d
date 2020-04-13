#pragma once

#include <string>
#include <vector>

#include "usls/scene/armature/Bone.h"


namespace usls::scene::armature
{
	class Armature
	{
	private:
		std::string											name;
		std::vector<Bone>									bones;
		std::vector<std::pair<std::string, size_t>>			animations;

		

	public:
															Armature(std::string name);
		void												addBone(Bone b);
		void												addAnimation(std::string name, size_t index);
		std::vector<Bone>&									getBones();
		const std::vector<Bone>&							getBones() const;
		const std::string&									getName() const;
		const std::vector<std::pair<std::string, size_t>>&	getAnimations() const;
		size_t												getBoneIndex(std::string boneName);

	};
}