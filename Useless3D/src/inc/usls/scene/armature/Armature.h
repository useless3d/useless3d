#pragma once

#include <string>
#include <vector>
#include <optional>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "usls/scene/animation/Animation.h"
#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/armature/Bone.h"
#include "usls/scene/stage/Transform.h"


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
		void												updateBone(size_t index, float time, glm::mat4 parentMatrix);
		glm::vec3											calcTranslation(const float& time, size_t currentKeyIndex, const usls::scene::animation::Channel& channel);
		glm::quat											calcRotation(const float& time, size_t currentKeyIndex, const usls::scene::animation::Channel& channel);
		glm::vec3											calcScale(const float& time, size_t currentKeyIndex, const usls::scene::animation::Channel& channel);
		usls::scene::stage::Transform						transform;


	public:
															Armature(std::string name);
		void												addBone(Bone b);
		void												addAnimation(std::string name, size_t index);
		Bone&												getRootBone();
		std::vector<Bone>&									getBones();
		const std::vector<Bone>&							getBones() const;
		Bone&												getBone(size_t index);
		Bone*												getBone(std::string boneName);
		const std::string&									getName() const;
		const std::vector<std::pair<std::string, size_t>>&	getAnimations() const;
		size_t												getBoneIndex(std::string boneName);
		void												setCurrentAnimation(std::string animationName);
		void												updateCurrentAnimation(double runTime, std::optional<glm::mat4> parentMatrix);
		size_t												getAnimationIndex(std::string animationName);
		usls::scene::stage::Transform&						getTransform();

	};
}