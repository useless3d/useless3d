#pragma once

#include <vector>
#include <string>
#include <optional>
#include <memory>

#include "glm/glm.hpp"

#include "usls/scene/Shader.h"
#include "usls/scene/stage/Camera.h"
#include "usls/scene/mesh/Vertex.h"
#include "usls/scene/mesh/Texture.h"
#include "usls/scene/mesh/Renderable.h"


namespace usls::scene::mesh
{
	class Mesh
	{

	private:
		std::string                         name;
		std::vector<Vertex>					vertices;
		std::vector<unsigned int>           indices;
		std::optional<size_t>               meshRenderableIndex;

	public:
		Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices);

		void                                setMeshRenderableIndex(size_t index);
		const std::optional<size_t>&        getMeshRenderableIndex() const;

		const std::string                   getName() const;
		const std::vector<Vertex>&			getVertices() const;
		const std::vector<unsigned int>&	getIndices() const;
		const bool                          isRenderable() const;

	};
    
}