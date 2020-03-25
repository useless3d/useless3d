#include <iostream>

#include "usls/scene/stage/Actor.h"

namespace usls
{
    Actor::Actor(std::string name, Transform t) :
        name(name),
        deleted(false),
        transform(t) 
    {}

    Actor::Actor(std::string name, Transform t, int meshIndex) :
        name(name),
        deleted(false),
        transform(t),
        meshIndex(meshIndex) 
    {}

    Actor::Actor(std::string name, Transform t, int meshIndex, int shaderIndex) :
        name(name),
        deleted(false),
        transform(t),
        meshIndex(meshIndex), 
        shaderIndex(shaderIndex)
    {}

    Actor::Actor(std::string name, Transform t, int meshIndex, int shaderIndex, int textureIndex) :
        name(name),
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

    const std::string Actor::getName() const
    {
        return this->name;
    }

    const std::optional<int>& Actor::getShaderIndex() const
    {
        return this->shaderIndex;
    }

    const std::optional<int>& Actor::getMeshIndex() const
    {
        return this->meshIndex;
    }

    const std::optional<int>& Actor::getTextureIndex() const
    {
        return this->textureIndex;
    }

    void Actor::addRenderCommand(std::pair<int, int> cmd)
    {
        this->renderCommand = cmd;
    }

}