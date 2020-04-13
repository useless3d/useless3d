#include <iostream>

#include "usls/scene/armature/Armature.h"


namespace usls::scene::armature
{
	Armature::Armature(std::string name) :
		name(name)
	{}
	
	const std::vector<std::pair<std::string, size_t>>& Armature::getAnimations() const
	{
		return this->animations;
	}

	const std::string& Armature::getName() const
	{
		return this->name;
	}

	void Armature::addAnimation(std::string name, size_t index)
	{
		this->animations.push_back(std::pair<std::string, size_t>(name, index));
	}

	void Armature::addBone(Bone b)
	{
		this->bones.push_back(b);
	}

	std::vector<Bone>& Armature::getBones()
	{
		return this->bones;
	}

	const std::vector<Bone>& Armature::getBones() const
	{
		return this->bones;
	}

	size_t Armature::getBoneIndex(std::string boneName)
	{
		for (size_t i = 0; i < this->bones.size(); i++)
		{
			if (this->bones.at(i).name == boneName)
			{
				return i;
			}
		}
		std::cout << "Trying to get index of non-existing boneName:" << boneName << "\n";
		std::cin.get();
		exit(EXIT_FAILURE);
	}

}