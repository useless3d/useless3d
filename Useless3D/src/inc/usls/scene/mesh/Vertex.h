#pragma once

#include "glm/glm.hpp"

#include "usls/scene/mesh/VertexBoneData.h"


namespace usls::scene::mesh
{
	struct Vertex
	{
		glm::vec3		position;
		glm::vec3		normal;
		glm::vec2		textureCoordinates;
		VertexBoneData	weights;

		bool operator==(const Vertex &) const;
	};      
}