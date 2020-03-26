#include <iostream>

#include "glad/glad.h"
#include "STB_IMAGE/stb_image.h"

#include "usls/GPU.h"
#include "usls/scene/mesh/MeshVertex.h"

namespace usls
{
    GPU::GPU(std::string shaderDirectory) :
        shaderDirectory(shaderDirectory)
    {}

    int GPU::loadShader(const std::string name, const std::string vertFile, const std::string fragFile)
    {
        unsigned int id;

        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            // open files
            vShaderFile.open(this->shaderDirectory + "/" + vertFile);
            fShaderFile.open(this->shaderDirectory + "/" + fragFile);

            std::stringstream vShaderStream, fShaderStream;

            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // close file handlers
            vShaderFile.close();
            fShaderFile.close();

            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2. compile shaders
        int success;
        char infoLog[512];


        // vertex Shader
        unsigned int vertex;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        // if compile errors, log and exit
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        };


        // fragment Shader
        unsigned int fragment;
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        // if compile errors, log and exit
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        };


        // shader Program
        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);

        // if linking errors, log and exit
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        this->shaders.push_back(Shader(name, id));

        return id;
    }

    int GPU::loadMesh(Mesh& m)
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

        this->meshRenderables.push_back(mr);

        return this->meshRenderables.size() - 1;
    }

    int GPU::loadTexture(std::string type, std::string path)
    {
        MeshTexture texture;
        texture.type = "diffuse";
        texture.path = path;

        glGenTextures(1, &texture.id);

        int width, height, nrComponents;
        //stbi_set_flip_vertically_on_load(true);
        unsigned char*	data = stbi_load(texture.path.c_str(), &width, &height, &nrComponents, 0);
        if (data) 
        {
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

            this->textures.push_back(texture);

            return this->textures.size() - 1;
        }
        else
        {
            stbi_image_free(data);
            std::cout << "Texture failed to load at path: " << texture.path << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }
    }

    const std::vector<MeshTexture>& GPU::getTextures() const
    {
        return this->textures;
    }

}