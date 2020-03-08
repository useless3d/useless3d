#include "usls/scene/Actor.h"

namespace usls
{
    Actor::Actor(Transformable& t) :
        Transformable(t)
    {

    }

    Actor::Actor(Transformable& t, Mesh* mesh) :
        mesh(mesh),
        Transformable(t)
    {
        
    }

    Actor::Actor(Transformable& t, Mesh* mesh, Camera* camera) :
        mesh(mesh),
        camera(camera),
        Transformable(t)
    {

    }

    void Actor::draw(Shader* shader)
    {
        if (this->mesh && this->camera) 
        {
            this->mesh.value()->draw(shader, this->camera.value(), this->getTransformMatrix());
        }
    }


}