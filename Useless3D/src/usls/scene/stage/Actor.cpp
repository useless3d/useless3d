#include <iostream>

#include "usls/scene/stage/Actor.h"

namespace usls
{
    Actor::Actor(std::string name, Transform t) :
        transform(t) {}

    Actor::Actor(std::string name, Transform t, int meshIndex) :
        transform(t),
        meshIndex(meshIndex) {}

    std::string Actor::getName()
    {
        return this->name;
    }

    //void Actor::draw(Shader* shader)
    //{
    //    if (this->mesh && this->camera) 
    //    {
    //        this->mesh.value()->draw(shader, this->camera.value(), this->getTransformMatrix());
    //    }
    //}


}