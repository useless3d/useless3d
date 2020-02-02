#pragma once

#include <vector>
#include <string>

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

namespace usls
{
    class Mesh 
    {

    private:
        unsigned int				VAO;
        unsigned int				VBO;
        unsigned int				EBO;
        std::vector<Vertex>			vertices;
        std::vector<unsigned int>	indices;
        Texture						texture;
        void						setupMesh();
        void						loadTexture(std::string path);

    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::string texturePath);
        ~Mesh();
        void						draw(Shader& shader);
        std::vector<Vertex>			getVerticies();
        std::vector<unsigned int>	getIndices();

    };
}