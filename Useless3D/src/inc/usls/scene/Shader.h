#pragma once

#include <string>

#include "glm/glm.hpp"

namespace usls 
{
    class Shader 
    {

    public:

        unsigned int ID; //program ID

        Shader() {};
        Shader(const std::string shaderDir, const std::string vertFile, const std::string fragFile);
        void use();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, glm::mat4 value) const;

    };
}