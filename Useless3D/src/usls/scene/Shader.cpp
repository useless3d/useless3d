#include <fstream>
#include <sstream>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

#include "usls/scene/Shader.h"
#include "usls/scene/Actor.h"


namespace usls
{

    Shader::Shader(std::string name, const std::string shaderDir, const std::string vertFile, const std::string fragFile) :
        name(name)
    {

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
            vShaderFile.open(shaderDir + "/" + vertFile);
            fShaderFile.open(shaderDir + "/" + fragFile);

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
        this->ID = glCreateProgram();
        glAttachShader(this->ID, vertex);
        glAttachShader(this->ID, fragment);
        glLinkProgram(this->ID);

        // if linking errors, log and exit
        glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }

        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }

    unsigned int Shader::getID()
    {
        return this->ID;
    }

    void Shader::use() 
    {
        glUseProgram(this->ID);
    }

    void Shader::setBool(const std::string & name, bool value) const 
    {
        glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string & name, int value) const 
    {
        glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
    }

    void Shader::setFloat(const std::string & name, float value) const
    {
        glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
    }

    void Shader::setMat4(const std::string & name, glm::mat4 value) const 
    {
        glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1,
            GL_FALSE, glm::value_ptr(value));
    }

}