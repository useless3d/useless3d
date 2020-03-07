#include "usls/scene/Actor.h"

namespace usls
{
    Actor::Actor(glm::vec3 translation, Rotation rotation, glm::vec3 scale) :
        Transformable(translation, rotation, scale)
    {

    }

    Actor::Actor(glm::vec3 translation, Rotation rotation, glm::vec3 scale, Mesh* mesh) :
        mesh(mesh),
        Transformable(translation, rotation, scale)
    {
        
    }

    void Actor::draw(Shader* shader)
    {
        if (this->mesh) 
        {
            this->mesh.value()->draw(shader, this->camera.value(), this->getMatrix());
        }
    }


}