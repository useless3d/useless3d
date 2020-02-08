#include <glad/glad.h>
#include <STB_IMAGE/stb_image.h>

#include <iostream>

#include "inc/Mesh.h"
#include "inc/Logger.h"

namespace usls
{

    std::vector<Mesh*>   Mesh::meshes;

    Mesh::Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture texture) :
        name(name),
        vertices(vertices),
        indices(indices),
        texture(texture)
    {
        //this->sendToGpu();
    }
    
    Mesh::~Mesh(){}

    //std::vector<Mesh*>   Mesh::meshes;

    Mesh* Mesh::createMesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture texture)
    {
        // Does the exact same mesh exist? If so return the pointer to that mesh.

        // Loop through each existing meshes and determine if the verticies, indicies, and texture(textures in the future) are the same.
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

    void Mesh::sendToGpu()
    {
        this->loadGpuTexture();

        // Generate and bind vertex attribute array
        glGenVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);

        // Generate and bind vertex buffer object
        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

        // Generate and bind element buffer object
        glGenBuffers(1, &this->EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

        // Assign vertex positions to location = 0
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // Assign vertex positions to location = 1
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        // Assign vertex texture coordinates to location = 2
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));


        // Unbind the vertex array to prevent accidental operations
        glBindVertexArray(0);
    }

    void Mesh::loadGpuTexture()
    {
        glGenTextures(1, &this->texture.id);

        int width, height, nrComponents;
        //stbi_set_flip_vertically_on_load(true);
        unsigned char*	data = stbi_load(this->texture.path.c_str(), &width, &height, &nrComponents, 0);
        if (data) {

            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, texture.id);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            if (Logger::isEnabled()) {
                Logger::log("Texture failed to load at path: " + this->texture.path);
            }
            stbi_image_free(data);
            exit(EXIT_FAILURE);
        }

    }

    Texture Mesh::getTexture()
    {
        return this->texture;
    }

    std::vector<Vertex> Mesh::getVertices() 
    {
        return this->vertices;
    }

    std::vector<unsigned int> Mesh::getIndices() 
    {
        return this->indices;
    }

    std::string Mesh::getName()
    {
        return this->name;
    }

    int Mesh::getMeshCount()
    {
        return Mesh::meshes.size();
    }

}