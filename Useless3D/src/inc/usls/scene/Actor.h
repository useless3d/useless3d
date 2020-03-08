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
        Actor(Transformable& t);
        Actor(Transformable& t, Mesh* mesh);
        Actor(Transformable& t, Mesh* mesh, Camera* camera);

        void draw(Shader* shader);

    };
}