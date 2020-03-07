#pragma once

#include <optional>
#include <string>

#include "glm/glm.hpp"

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/camera/Camera.h"
#include "usls/scene/transformable/Transformable.h"
#include "usls/scene/transformable/Rotation.h"

namespace usls
{
    class Actor : public Transformable
    {
    private:
        std::optional<Mesh*>    mesh;
        std::optional<Camera*>  camera;

    public:
        Actor(glm::vec3 translation, Rotation rotation, glm::vec3 scale);
        Actor(glm::vec3 translation, Rotation rotation, glm::vec3 scale, Mesh* mesh);

        void draw(Shader* shader);

    };
}