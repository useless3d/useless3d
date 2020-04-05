#pragma once

#include "glm/glm.hpp"

#include "usls/scene/transform/Rotation.h"

namespace usls::scene::transform
{

	class Transform
	{
	private:
		glm::vec3	translation;
		Rotation	rotation;
		glm::vec3	scale;

	public:
		Transform();
		Transform(glm::vec3 t, Rotation r, glm::vec3 s);

		void		setTranslation(glm::vec3 translation);
		void		setRotation(float angle, glm::vec3 axis);
		void		setScale(glm::vec3 scale);
		glm::vec3   getTranslation();
		Rotation    getRotation();
		glm::vec3   getScale();
		const glm::mat4   getMatrix() const;
		void        print();
	};
	
    
}