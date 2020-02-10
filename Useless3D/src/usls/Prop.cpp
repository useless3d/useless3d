#include "inc/Prop.h"

namespace usls
{

    Prop::Prop(Mesh* mesh, glm::vec3 translation, Rotation rotation, glm::vec3 scale) :
        mesh(mesh),
        Transformable(translation, rotation, scale)
    {

    }
    Prop::~Prop() {}

}