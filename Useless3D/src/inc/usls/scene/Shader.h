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
        std::vector<Actor*> actors;

    public:

        unsigned int ID; //program ID

        Shader(const std::string shaderDir, const std::string vertFile, const std::string fragFile);

        void addActor(Actor* a);
        void draw();

        void use();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, glm::mat4 value) const;

    };
}