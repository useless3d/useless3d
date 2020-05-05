#include <iostream>

#define GLM_FORCE_ALIGNED_GENTYPES
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/string_cast.hpp>

#include "usls/App.h"
#include "usls/scene/armature/Armature.h"


namespace usls::scene::armature
{
	Armature::Armature(std::string name) :
		name(name)
	{}

	glm::vec3 Armature::calcTranslation(const float& time, size_t currentKeyIndex, const usls::scene::animation::Channel& channel)
	{
		size_t nextKeyIndex = currentKeyIndex + 1;

		float deltaTime = channel.positionKeyTimes[nextKeyIndex] - channel.positionKeyTimes[currentKeyIndex];
		float factor = ((time - channel.positionKeyTimes[currentKeyIndex]) / deltaTime);

		return channel.positionKeyValues[currentKeyIndex] + factor * (channel.positionKeyValues[nextKeyIndex] - channel.positionKeyValues[currentKeyIndex]);
	}

	glm::quat Armature::calcRotation(const float& time, size_t currentKeyIndex, const usls::scene::animation::Channel& channel)
	{
		size_t nextKeyIndex = currentKeyIndex + 1;

		float deltaTime = channel.rotationKeyTimes[nextKeyIndex] - channel.rotationKeyTimes[currentKeyIndex];
		float factor = ((time - channel.rotationKeyTimes[currentKeyIndex]) / deltaTime);

		return glm::normalize(glm::slerp(channel.rotationKeyValues[currentKeyIndex], channel.rotationKeyValues[nextKeyIndex], factor));
	}

	glm::vec3 Armature::calcScale(const float& time, size_t currentKeyIndex, const usls::scene::animation::Channel& channel)
	{
		size_t nextKeyIndex = currentKeyIndex + 1;

		float deltaTime = channel.scalingKeyTimes[nextKeyIndex] - channel.scalingKeyTimes[currentKeyIndex];
		float factor = ((time - channel.scalingKeyTimes[currentKeyIndex]) / deltaTime);

		return channel.scalingKeyValues[currentKeyIndex] + factor * (channel.scalingKeyValues[nextKeyIndex] - channel.scalingKeyValues[currentKeyIndex]);
	}

	void Armature::updateBone(size_t index, float time, glm::mat4 parentMatrix)
	{
		auto& bone = this->bones[index];
		auto& channel = this->currentAnimation->channels[bone.name];

		auto it = std::upper_bound(channel.positionKeyTimes.begin(), channel.positionKeyTimes.end(), time);
		auto tmpKey = (size_t)(it - channel.positionKeyTimes.begin());
		auto currentKeyIndex = time > channel.positionKeyTimes[tmpKey] ? 0 : tmpKey - 1;

		// calc* methods no longer check for condition where only one key exists...could be an issue in the future

		bone.matrix = glm::mat4(1.0f);
		bone.matrix = glm::translate(bone.matrix, this->calcTranslation(time, currentKeyIndex, channel));
		bone.matrix = bone.matrix * glm::toMat4(this->calcRotation(time, currentKeyIndex, channel));
		bone.matrix = glm::scale(bone.matrix, this->calcScale(time, currentKeyIndex, channel));
		bone.matrix = parentMatrix * bone.matrix;
	}

	void Armature::updateCurrentAnimation(double runTime, std::optional<glm::mat4> parentMatrix)
	{
		double timeInTicks = runTime * this->currentAnimation->tps;
		double animationTime = fmod(timeInTicks, this->currentAnimation->duration);

		for (size_t i = 0; i < this->bones.size(); i++)
		{
			if (i == 0)
			{
				this->updateBone(0, (float)animationTime, glm::mat4(1.0f));
			}
			else
			{
				this->updateBone(i, (float)animationTime, this->bones[this->bones[i].parent].matrix);
			}
		}
	}

	void Armature::setCurrentAnimation(std::string animationName)
	{
		this->currentAnimationName = animationName;
		this->currentAnimation = &App::get().getScene()->getAnimation(this->getAnimationIndex(this->currentAnimationName));
	}

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

	Bone& Armature::getRootBone()
	{
		return this->bones[0];
	}

	std::vector<Bone>& Armature::getBones()
	{
		return this->bones;
	}

	const std::vector<Bone>& Armature::getBones() const
	{
		return this->bones;
	}

	Bone* Armature::getBone(std::string boneName)
	{
		for (auto& b : this->bones)
		{
			if (b.name == boneName)
				return &b;
		}
		return nullptr;
	}

	Bone& Armature::getBone(size_t index)
	{
		return this->bones.at(index);
	}

	size_t Armature::getAnimationIndex(std::string animationName)
	{
		for (auto& p : this->animations)
		{
			if (p.first == animationName)
			{
				return p.second;
			}
		}
		std::cout << "Trying to get index of non-existing animationName:" << animationName << "\n";
		std::cin.get();
		exit(EXIT_FAILURE);
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