#include <glad/glad.h>
#include <STB_IMAGE/stb_image.h>

#include "inc/Renderable.h"
#include "inc/Logger.h"

#include <iostream>

#include <glm/gtx/string_cast.hpp>



namespace usls
{
    Renderable::Renderable(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture texture) :
        texture(texture),
        indiceCount(indices.size())
    {
        this->sendToGPU(vertices, indices);        
    }

    Renderable::~Renderable() 
    {
        std::cout << "Destructor Called\n";
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
        glDeleteBuffers(1, &this->EBO);
        glDeleteTextures(1, &this->texture.id);
    }

    void Renderable::loadTexture()
    {
        if (this->texture.path == "")
        {
            return;
        }

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

    void Renderable::sendToGPU(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    {
        this->loadTexture();

        // Generate and bind vertex attribute array
        glGenVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);

        // Generate and bind vertex buffer object
        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        // Generate and bind element buffer object
        glGenBuffers(1, &this->EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

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

    const Texture& Renderable::getTexture() const
    {
        return this->texture;
    }

    void Renderable::draw(Shader* shader, Camera* camera, glm::mat4 modelMatrix)
    {

        shader->use();
        shader->setMat4("mvp", camera->getProjectionMatrix() * camera->getViewMatrix() * modelMatrix);

        // activate proper texture unit before binding
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture.id);
        shader->setInt("texture1", 0);

        // draw mesh
        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, this->indiceCount, GL_UNSIGNED_INT, 0);

        // set everything back to defaults once configured
        glBindVertexArray(0);
    }

}