#pragma once

#include <optional>
#include <string>

#include "glm/glm.hpp"

#include "usls/scene/stage/mesh/Mesh.h"
#include "usls/scene/Shader.h"
#include "usls/scene/stage/camera/camera.h"
#include "usls/scene/stage/transformable/Transformable.h"

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

        void draw(Shader* appOrStageShader, Camera* camera);

    };
}