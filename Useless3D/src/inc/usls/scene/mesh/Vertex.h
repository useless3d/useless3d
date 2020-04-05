#pragma once

#include "glm/glm.hpp"

namespace usls::scene::mesh
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 textureCoordinates;

		bool operator==(const Vertex &) const;
	};      
}