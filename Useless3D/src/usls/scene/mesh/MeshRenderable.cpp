#include <iostream>

#include "glad/glad.h"
#include "STB_IMAGE/stb_image.h"
#include "glm/gtx/string_cast.hpp"

#include "usls/scene/mesh/MeshRenderable.h"



namespace usls
{
    MeshRenderable::MeshRenderable(const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices, MeshTexture texture) :
        texture(texture),
        indiceCount(indices.size())
    {
        this->sendToGPU(vertices, indices);        
    }

    MeshRenderable::~MeshRenderable()
    {
        std::cout << "Destructor Called\n";
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
        glDeleteBuffers(1, &this->EBO);
        glDeleteTextures(1, &this->texture.id);
    }

    void MeshRenderable::loadTexture()
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
            stbi_image_free(data);
            std::cout << "Texture failed to load at path: " << this->texture.path << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }
    }

    void MeshRenderable::sendToGPU(const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices)
    {
        this->loadTexture();

        // Generate and bind vertex attribute array
        glGenVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);

        // Generate and bind vertex buffer object
        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MeshVertex), &vertices[0], GL_STATIC_DRAW);

        // Generate and bind element buffer object
        glGenBuffers(1, &this->EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // Assign vertex positions to location = 0
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)0);

        // Assign vertex positions to location = 1
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, normal));

        // Assign vertex texture coordinates to location = 2
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, textureCoordinates));

        // Unbind the vertex array to prevent accidental operations
        glBindVertexArray(0);
    }

    const MeshTexture& MeshRenderable::getTexture() const
    {
        return this->texture;
    }

    void MeshRenderable::draw(Shader* shader, Camera* camera, glm::mat4 modelMatrix)
    {
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