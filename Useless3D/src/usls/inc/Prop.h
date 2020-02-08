#pragma once

#include "Transformable.h"
#include "Mesh.h"

namespace usls
{
    class Prop : public Transformable
    {
    private:
        Mesh*   mesh;

    public:
        Prop(Mesh* mesh, glm::vec3 translation, Rotation rotation, glm::vec3 scale);
        ~Prop();
        Mesh*   getMesh();
    };
}