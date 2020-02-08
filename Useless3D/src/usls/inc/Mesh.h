#pragma once

#include <glad/glad.h>
#include <STB_IMAGE/stb_image.h>

#include <vector>
#include <string>
#include <memory>
#include "Vertex.h"
#include "Texture.h"

namespace usls
{
    // Private constructor so same mesh is not created twice, return existing pointer if mesh
    // to be created is an instance of an already instantiated mesh. This is to be
    // determined by the "name" parameter
    class Mesh 
    {

    private:
        ~Mesh();
        Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture texture);
        static std::vector<Mesh*>   meshes;

        void                        sendToGpu();
        void                        loadGpuTexture();


        std::string                 name;
        std::vector<Vertex>			vertices;
        std::vector<unsigned int>   indices;

        Texture						texture;
        unsigned int				VAO;
        unsigned int				VBO;
        unsigned int				EBO;


    public:
        
        static Mesh*                createMesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture texture);
        static int                  getMeshCount();
        std::vector<Vertex>			getVertices();
        std::vector<unsigned int>	getIndices();
        std::string                 getName();
        Texture                     getTexture();

    };
}