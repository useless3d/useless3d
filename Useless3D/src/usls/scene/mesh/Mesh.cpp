#include <iostream>


#include "glad/glad.h"
#include "STB_IMAGE/stb_image.h"

#include "usls/scene/mesh/Mesh.h"


namespace usls
{

    Mesh::Mesh(std::string name, std::vector<MeshVertex> vertices, std::vector<unsigned int> indices) :
        name(name),
        vertices(vertices),
        indices(indices)
    {
        
    }

    void Mesh::setMeshRenderableIndex(int index)
    {
        this->meshRenderableIndex = index;
    }

    const std::vector<MeshVertex>& Mesh::getVertices() const
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

    const std::optional<int>& Mesh::getMeshRenderableIndex() const
    {
        return this->meshRenderableIndex;
    }

}