#include <iostream>

#include "usls/scene/stage/Actor.h"

namespace usls::scene::stage
{
    Actor::Actor(std::string name, Transform t) :
        name(name),
        deleted(false),
        transform(t) 
    {}

    void Actor::setMeshIndex(int i)
    {
        this->meshIndex = i;
    }

    void Actor::setShaderIndex(int i)
    {
        this->shaderIndex = i;
    }

    void Actor::setTextureIndex(int i)
    {
        this->textureIndex = i;
    }

    Transform& Actor::getTransform()
    {
        return this->transform;
    }

    const bool Actor::isDeleted() const
    {
        return this->deleted;
    }

    void Actor::setDeleted(bool d)
    {
        this->deleted = d;
    }

    const std::pair<int, int>& Actor::getRenderCommand() const
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