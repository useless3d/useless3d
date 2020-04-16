#include <iostream>


#include "glad/glad.h"
#include "STB_IMAGE/stb_image.h"

#include "usls/scene/mesh/Mesh.h"


namespace usls::scene::mesh
{

    Mesh::Mesh(std::string name) :
        name(name)
    {}

	Bone& Mesh::getBone(size_t index)
	{
		return this->bones.at(index);
	}

	glm::mat4 Mesh::getGlobalInverseMatrix()
	{
		return this->globalInverseMatrix;
	}

	void Mesh::setGlobalInverseMatrix(glm::mat4 gim)
	{
		this->globalInverseMatrix = gim;
	}

	const bool Mesh::hasBones() const
	{
		if (this->bones.size() > 0)
		{
			return true;
		}
		return false;
	}

	void Mesh::addVertexWeight(unsigned int vertexIndex, unsigned int boneIndex, float weight)
	{
		// I'm not a fan of this...seems complex for just adding something to a raw array...why not just use a vector?
		for (unsigned int i = 0; i < (sizeof(this->vertexWeights[vertexIndex].ids) / sizeof(this->vertexWeights[vertexIndex].ids[0])); i++)
		{
			if (this->vertexWeights[vertexIndex].weights[i] == 0.0)
			{
				this->vertexWeights[vertexIndex].ids[i] = boneIndex;
				this->vertexWeights[vertexIndex].weights[i] = weight;
				return;
			}
		}		
	}

	void Mesh::resizeVertexWeights(size_t size)
	{
		this->vertexWeights.resize(size);
	}

	void Mesh::setVertices(std::vector<Vertex>& vertices)
	{
		this->vertices = vertices;
	}

	void Mesh::setIndices(std::vector<unsigned int>& indices)
	{
		this->indices = indices;
	}

	void Mesh::setBones(std::vector<Bone>& bones)
	{
		this->bones = bones;
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

}