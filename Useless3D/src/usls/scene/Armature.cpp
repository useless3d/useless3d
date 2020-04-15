#include <iostream>

#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/matrix_decompose.hpp>

#include "usls/App.h"
#include "usls/scene/armature/Armature.h"


namespace usls::scene::armature
{
	Armature::Armature(std::string name) :
		name(name)
	{}

	glm::vec3 Armature::calcTranslation(const double& time, const usls::scene::animation::Channel& channel)
	{
		if (channel.positionKeys.size() == 1)
		{
			return channel.positionKeys[0].second;
		}

		size_t currentKeyIndex = 0;
		for (size_t i = 0; i < channel.positionKeys.size() - 1; i++)
		{
			if (time < channel.positionKeys[i + 1].first)
			{
				currentKeyIndex = i;
			}
		}

		size_t nextKeyIndex = currentKeyIndex + 1;

		double deltaTime = channel.positionKeys[nextKeyIndex].first - channel.positionKeys[currentKeyIndex].first;
		double factor = time - channel.positionKeys[currentKeyIndex].first / deltaTime;

		glm::vec3 start = channel.positionKeys[currentKeyIndex].second;
		glm::vec3 end = channel.positionKeys[nextKeyIndex].second;
		glm::vec3 delta = end - start;

		glm::vec3 returnVal = start + (float)factor * delta;

		//std::cout << "(" << returnVal.x << "," << returnVal.y << "," << returnVal.z << ")\n";

		return returnVal;
	}

	glm::quat Armature::calcRotation(const double& time, const usls::scene::animation::Channel& channel)
	{
		if (channel.rotationKeys.size() == 1)
		{
			return channel.rotationKeys[0].second;
		}

		size_t currentKeyIndex = 0;
		for (size_t i = 0; i < channel.rotationKeys.size() - 1; i++)
		{
			if (time < channel.rotationKeys[i + 1].first)
			{
				currentKeyIndex = i;
			}
		}

		size_t nextKeyIndex = currentKeyIndex + 1;

		double deltaTime = channel.rotationKeys[nextKeyIndex].first - channel.rotationKeys[currentKeyIndex].first;
		double factor = time - channel.rotationKeys[currentKeyIndex].first / deltaTime;

		glm::quat start = channel.rotationKeys[currentKeyIndex].second;
		glm::quat end = channel.rotationKeys[nextKeyIndex].second;
		glm::quat delta = glm::slerp(start, end, (float)factor);
		delta = glm::normalize(delta);
		
		//std::cout << "(" << delta.x << "," << delta.y << "," << delta.z << "," << delta.w <<  ")\n";

		return delta;
	}

	glm::vec3 Armature::calcScale(const double& time, const usls::scene::animation::Channel& channel)
	{
		if (channel.scalingKeys.size() == 1)
		{
			return channel.scalingKeys[0].second;
		}

		size_t currentKeyIndex = 0;
		for (size_t i = 0; i < channel.scalingKeys.size() - 1; i++)
		{
			if (time < channel.scalingKeys[i + 1].first)
			{
				currentKeyIndex = i;
			}
		}

		size_t nextKeyIndex = currentKeyIndex + 1;

		double deltaTime = channel.scalingKeys[nextKeyIndex].first - channel.scalingKeys[currentKeyIndex].first;
		double factor = time - channel.scalingKeys[currentKeyIndex].first / deltaTime;

		glm::vec3 start = channel.scalingKeys[currentKeyIndex].second;
		glm::vec3 end = channel.scalingKeys[nextKeyIndex].second;
		glm::vec3 delta = end - start;

		glm::vec3 returnVal = start + (float)factor * delta;

		//std::cout << "(" << returnVal.x << "," << returnVal.y << "," << returnVal.z << ")\n";

		return returnVal;
	}

	void Armature::updateBone(size_t index, double time, glm::mat4 parentMatrix)
	{
		auto& bone = this->bones[index];
		usls::scene::animation::Channel channel;

		for (auto& c : this->currentAnimation->channels)
		{
			if (c.name == bone.name)
			{
				channel = c;
				break;
			}
		}

		auto boneMatrix = glm::mat4(1.0f);
		boneMatrix = glm::translate(boneMatrix, this->calcTranslation(time, channel));
		boneMatrix = boneMatrix * glm::toMat4(this->calcRotation(time, channel));
		boneMatrix = glm::scale(boneMatrix, this->calcScale(time, channel));
		boneMatrix = parentMatrix * boneMatrix;

		// Decompose matrix so we can save it's independant values to the bone's transform
		// (so it's position, rotation, scale can be referenced later for things such as parenting)
		glm::vec3 scale;
		glm::quat rotation; 
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(boneMatrix, scale, rotation, translation, skew, perspective);

		bone.worldTransform.setTranslation(translation);
		bone.worldTransform.setRotation(glm::conjugate(rotation)); // decompose returns rotation conjugate, so this is compensated for
		bone.worldTransform.setScale(scale);

		for (auto& c : bone.children)
		{
			this->updateBone(c, time, boneMatrix);
		}
	}

	void Armature::updateCurrentAnimation(double runTime)
	{
		double timeInTicks = runTime * this->currentAnimation->tps;
		double animationTime = fmod(timeInTicks, this->currentAnimation->duration);

		this->updateBone(0, animationTime, glm::mat4(1.0f));

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

	std::vector<Bone>& Armature::getBones()
	{
		return this->bones;
	}

	const std::vector<Bone>& Armature::getBones() const
	{
		return this->bones;
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