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

	glm::vec3 Armature::calcTranslation(const double& time, size_t currentKeyIndex, const usls::scene::animation::Channel& channel)
	{
		// no longer checking for condition where only one key exists...could be an issue in the future

		size_t nextKeyIndex = currentKeyIndex + 1;

		double deltaTime = channel.positionKeyTimes[nextKeyIndex] - channel.positionKeyTimes[currentKeyIndex];
		double factor = time - channel.positionKeyTimes[currentKeyIndex] / deltaTime;

		glm::vec3 start = channel.positionKeyValues[currentKeyIndex];
		glm::vec3 end = channel.positionKeyValues[nextKeyIndex];
		glm::vec3 delta = end - start;

		glm::vec3 returnVal = start + (float)factor * delta;

		return returnVal;
	}

	glm::quat Armature::calcRotation(const double& time, size_t currentKeyIndex, const usls::scene::animation::Channel& channel)
	{
		// no longer checking for condition where only one key exists...could be an issue in the future

		size_t nextKeyIndex = currentKeyIndex + 1;

		double deltaTime = channel.rotationKeyTimes[nextKeyIndex] - channel.rotationKeyTimes[currentKeyIndex];
		float factor = (float)((time - channel.rotationKeyTimes[currentKeyIndex]) / deltaTime);

		glm::quat start = channel.rotationKeyValues[currentKeyIndex];
		glm::quat end = channel.rotationKeyValues[nextKeyIndex];
		glm::quat delta = glm::normalize(glm::slerp(start, end, factor));

		return delta;
	}

	glm::vec3 Armature::calcScale(const double& time, size_t currentKeyIndex, const usls::scene::animation::Channel& channel)
	{
		// no longer checking for condition where only one key exists...could be an issue in the future

		size_t nextKeyIndex = currentKeyIndex + 1;

		double deltaTime = channel.scalingKeyTimes[nextKeyIndex] - channel.scalingKeyTimes[currentKeyIndex];
		double factor = time - channel.scalingKeyTimes[currentKeyIndex] / deltaTime;

		glm::vec3 start = channel.scalingKeyValues[currentKeyIndex];
		glm::vec3 end = channel.scalingKeyValues[nextKeyIndex];
		glm::vec3 delta = end - start;

		glm::vec3 returnVal = start + (float)factor * delta;

		return returnVal;
	}

	void Armature::updateBone(size_t index, double time, glm::mat4 parentMatrix)
	{
		auto& bone = this->bones[index];
		auto& channel = this->currentAnimation->channels[bone.name];

		auto it = std::upper_bound(channel.positionKeyTimes.begin(), channel.positionKeyTimes.end(), time);
		auto tmpKey = (size_t)(it - channel.positionKeyTimes.begin());
		auto currentKeyIndex = time > channel.positionKeyTimes[tmpKey] ? 0 : tmpKey - 1;

		bone.matrix = glm::mat4(1.0f);
		bone.matrix = glm::translate(bone.matrix, this->calcTranslation(time, currentKeyIndex, channel));
		bone.matrix = bone.matrix * glm::toMat4(this->calcRotation(time, currentKeyIndex, channel));
		bone.matrix = glm::scale(bone.matrix, this->calcScale(time, currentKeyIndex, channel));
		bone.matrix = parentMatrix * bone.matrix;
	}

	void Armature::updateCurrentAnimation(double runTime)
	{
		double timeInTicks = runTime * this->currentAnimation->tps;
		double animationTime = fmod(timeInTicks, this->currentAnimation->duration);

		for (size_t i = 0; i < this->bones.size(); i++)
		{
			if (i == 0)
			{
				this->updateBone(0, animationTime, this->transform.getMatrix());
			}
			else
			{
				this->updateBone(i, animationTime, this->bones[this->bones[i].parent].matrix);
			}
		}
	}

	void Armature::setCurrentAnimation(std::string animationName)
	{
		this->currentAnimationName = animationName;
		this->currentAnimation = &App::get().getScene()->getAnimation(this->getAnimationIndex(this->currentAnimationName));
	}

	usls::scene::stage::Transform& Armature::getTransform() 
	{
		return this->transform;
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