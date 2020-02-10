#pragma once

#include "Transformable.h"
#include "Mesh.h"

namespace usls
{
    class Prop : public Transformable
    {
    private:
        Mesh* const mesh;

    public:
        Prop(Mesh* const mesh, glm::vec3 translation, Rotation rotation, glm::vec3 scale);
        ~Prop();

    };
}