#pragma once

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "usls/scene/animation/Animation.h"
#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/armature/Bone.h"


namespace usls::scene::armature
{
	class Armature
	{
	private:
		std::string											name;
		std::vector<Bone>									bones;
		std::vector<std::pair<std::string, size_t>>			animations;
		std::string											currentAnimationName;
		usls::scene::animation::Animation*					currentAnimation;

		void												updateBone(size_t index, double time);

		glm::vec3											calcTranslation(const double& time, const usls::scene::animation::Channel& channel);
		//glm::quat											calcRotation(const double& time, const usls::scene::animation::Channel& channel);
		//glm::vec3											calcScale(const double& time, const usls::scene::animation::Channel& channel);

	public:
															Armature(std::string name);
		void												addBone(Bone b);
		void												addAnimation(std::string name, size_t index);
		std::vector<Bone>&									getBones();
		const std::vector<Bone>&							getBones() const;
		const std::string&									getName() const;
		const std::vector<std::pair<std::string, size_t>>&	getAnimations() const;
		size_t												getBoneIndex(std::string boneName);
		void												setCurrentAnimation(std::string animationName);
		void												updateCurrentAnimation(double runTime);
		size_t												getAnimationIndex(std::string animationName);

	};
}