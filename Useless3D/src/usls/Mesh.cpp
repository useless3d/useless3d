#include <glad/glad.h>
#include <STB_IMAGE/stb_image.h>

#include <iostream>

#include "inc/Mesh.h"
#include "inc/Logger.h"

namespace usls
{

    Mesh::Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices) :
        name(name),
        vertices(vertices),
        indices(indices)
    {
        
    }

    void Mesh::makeRenderable(Texture texture)
    {
        this->renderable = std::move(std::make_unique<Renderable>(this->vertices, this->indices, texture));
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
        return this->renderable.has_value();
    }

    const std::string Mesh::getTexturePath() const
    {
        return this->renderable.value()->getTexture().path;
    }

    void Mesh::draw(Shader* shader, Camera* camera, glm::mat4 modelMatrix)
    {
        if (this->isRenderable())
        {
            this->renderable.value()->draw(shader, camera, modelMatrix);
        }
    }

}