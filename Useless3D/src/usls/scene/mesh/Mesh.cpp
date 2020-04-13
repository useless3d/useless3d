#include <iostream>


#include "glad/glad.h"
#include "STB_IMAGE/stb_image.h"

#include "usls/scene/mesh/Mesh.h"


namespace usls::scene::mesh
{

    Mesh::Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices) :
        name(name),
        vertices(vertices),
        indices(indices)
    {
        
    }

    void Mesh::setMeshRenderableIndex(size_t index)
    {
        this->meshRenderableIndex = index;
    }

    const std::vector<Vertex>& Mesh::getVertices() const
    {
        return this->vertices;
    }

    const std::vector<unsigned int>& Mesh::getIndices() const
    {
        return this->indices;
    }

    const std::string Mesh::getName() const
    {
        return this->name;
    }

    const bool Mesh::isRenderable() const
    {
        return this->meshRenderableIndex.has_value();
    }

    const std::optional<size_t>& Mesh::getMeshRenderableIndex() const
    {
        return this->meshRenderableIndex;
    }

	void Mesh::setBones(std::vector<Bone>& bones)
	{
		this->bones = bones;
	}

}