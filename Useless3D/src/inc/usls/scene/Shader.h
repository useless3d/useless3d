#pragma once

#include <string>
#include <vector>

#include "glm/glm.hpp"

namespace usls 
{
    class Actor;

    class Shader 
    {
    private:
        const unsigned int id;
        const std::string name;

    public:
        Shader(const std::string name, unsigned int id);
        const unsigned int getId();
        void use();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, glm::mat4 value) const;

    };
}