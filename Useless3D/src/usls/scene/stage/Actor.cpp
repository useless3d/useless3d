#include <iostream>

#include "usls/scene/stage/Actor.h"

namespace usls
{
    Actor::Actor(std::string name, Transform t) :
        deleted(false),
        transform(t) 
    {}

    Actor::Actor(std::string name, Transform t, int meshIndex) :
        deleted(false),
        transform(t),
        meshIndex(meshIndex) 
    {}

    Actor::Actor(std::string name, Transform t, int meshIndex, int shaderIndex) :
        deleted(false),
        transform(t),
        meshIndex(meshIndex), 
        shaderIndex(shaderIndex)
    {}

    Actor::Actor(std::string name, Transform t, int meshIndex, int shaderIndex, int textureIndex) :
        deleted(false),
        transform(t),
        meshIndex(meshIndex),
        shaderIndex(shaderIndex),
        textureIndex(textureIndex)
    {}

    void Actor::setDeleted(bool d)
    {
        this->deleted = d;
    }

    std::pair<int, int>& Actor::getRenderCommand()
    {
        return this->renderCommand.value();
    }

    std::string Actor::getName()
    {
        return this->name;
    }

    int Actor::getShaderIndex()
    {
        return this->shaderIndex.value();
    }

    int Actor::getMeshIndex()
    {
        return this->meshIndex.value();
    }

    int Actor::getTextureIndex()
    {
        return this->textureIndex.value();
    }

    void Actor::addRenderCommand(std::pair<int, int> cmd)
    {
        this->renderCommand = cmd;
    }

}