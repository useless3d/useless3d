#include <iostream>

#include "glad/glad.h"
#include "STB_IMAGE/stb_image.h"

#include "usls/GPU.h"
#include "usls/scene/mesh/MeshVertex.h"

namespace usls
{
    void GPU::loadMesh(Mesh& m)
    {
        MeshRenderable mr = MeshRenderable();
        mr.indiceCount = m.getIndices().size();

        // Generate and bind vertex attribute array
        glGenVertexArrays(1, &mr.VAO);
        glBindVertexArray(mr.VAO);

        // Generate and bind vertex buffer object
        glGenBuffers(1, &mr.VBO);
        glBindBuffer(GL_ARRAY_BUFFER, mr.VBO);
        glBufferData(GL_ARRAY_BUFFER, m.getVertices().size() * sizeof(MeshVertex), &m.getVertices()[0], GL_STATIC_DRAW);

        // Generate and bind element buffer object
        glGenBuffers(1, &mr.EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mr.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.getIndices().size() * sizeof(unsigned int), &m.getIndices()[0], GL_STATIC_DRAW);

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

        // Assign this MeshRenderable to the mesh m
        m.setRenderable(mr);
    }

    void GPU::loadTexture(MeshTexture& mt)
    {
        glGenTextures(1, &mt.id);

        int width, height, nrComponents;
        //stbi_set_flip_vertically_on_load(true);
        unsigned char*	data = stbi_load(mt.path.c_str(), &width, &height, &nrComponents, 0);
        if (data) 
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, mt.id);
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
            std::cout << "Texture failed to load at path: " << mt.path << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }
    }

}