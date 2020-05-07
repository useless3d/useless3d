
#include "glm/gtx/compatibility.hpp"

#include "usls/scene/stage/Transform.h"
#include "usls/scene/armature/Bone.h"

namespace usls::scene::armature
{
	glm::mat4 Bone::getRenderMatrix(float alpha)
	{
		usls::scene::stage::Transform t;
		t.setTranslation(glm::lerp(this->previousTranslation, this->translation, alpha));
		t.setRotation(glm::slerp(this->previousRotation, this->rotation, alpha));
		t.setScale(glm::lerp(this->previousScale, this->scale, alpha));
		return t.getMatrix();
	}
}