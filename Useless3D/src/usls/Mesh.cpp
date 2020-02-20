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
        this->renderable = Renderable(this->vertices, this->indices, texture); // if you see intellisense error here ignore, it builds fine on all compilers
    }

    /*
    Mesh* Mesh::createMesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture texture)
    {
        // Does the exact same mesh exist? If so return the pointer to that mesh.

        // Loop through each existing meshes and determine if the verticies, indicies, and texture(textures in the future) are the same.
        // (I can't imagine this will scale well, and a more clever solution should be implemented in the future, BUT premature optimization never helped anyone)
        // AND keep in mind this is only insuring that a single VBO/EBO/VAO/Texture are sent to the gpu for drawing...we will still need to implement
        // "instancing" so all instances can be drawn with a single draw call in the future.
        for (int i = 0; i < Mesh::meshes.size(); i++)
        {
            if (vertices == Mesh::meshes[i]->getVertices() && indices == Mesh::meshes[i]->getIndices() && texture.path == Mesh::meshes[i]->getTexture().path) 
            {
                return Mesh::meshes[i];
            }
        }

        // There is no existing mesh for this data, create a new meshes pointer and return
        Mesh* newMesh = new Mesh(name, vertices, indices, texture);
        Mesh::meshes.push_back(newMesh);
        return newMesh;
    }
    */

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

    const Renderable& Mesh::getRenderable() const
    {
        if (this->renderable)
        {
            return this->renderable.value();
        }
    }

    const bool Mesh::isRenderable() const
    {
        return this->renderable.has_value();
    }

    void Mesh::draw(Shader* shader)
    {
        if (this->isRenderable())
        {
            this->renderable.value().draw(shader);
        }
    }

}