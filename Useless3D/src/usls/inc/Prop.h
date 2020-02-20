#pragma once

#include <optional>
#include <string>

#include "Transformable.h"
#include "Mesh.h"
#include "Shader.h"

namespace usls
{
    class Prop : public Transformable
    {
    private:
        std::optional<Mesh*>    mesh;
        std::string             name;

    public:
        Prop(std::string name, glm::vec3 translation, Rotation rotation, glm::vec3 scale, Mesh* mesh);
        ~Prop();

        void draw(Shader* appOrStageShader);

    };
}