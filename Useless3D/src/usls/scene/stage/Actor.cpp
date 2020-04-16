#include <iostream>

#include "usls/App.h"
#include "usls/scene/stage/Actor.h"

namespace usls::scene::stage
{
    Actor::Actor(std::string name, Transform t) :
        name(name),
        deleted(false),
        transform(t) 
    {}

    void Actor::setMeshIndex(size_t i)
    {
        this->meshIndex = i;
    }

    void Actor::setShaderIndex(size_t i)
    {
        this->shaderIndex = i;
    }

    void Actor::setTextureIndex(size_t i)
    {
        this->textureIndex = i;
    }

	void Actor::setArmatureIndex(size_t i)
	{
		this->armatureIndex = i;
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

    const std::pair<size_t, size_t>& Actor::getRenderCommand() const
    {
        return this->renderCommand.value();
    }

    const std::string Actor::getName() const
    {
        return this->name;
    }

    const std::optional<size_t>& Actor::getShaderIndex() const
    {
        return this->shaderIndex;
    }

    const std::optional<size_t>& Actor::getMeshIndex() const
    {
        return this->meshIndex;
    }

    const std::optional<size_t>& Actor::getTextureIndex() const
    {
        return this->textureIndex;
    }

    void Actor::addRenderCommand(std::pair<size_t, size_t> cmd)
    {
        this->renderCommand = cmd;
    }

	const bool Actor::isAnimated() const
	{
		if (this->armatureIndex) 
		{
			return true;
		}
		return false;
	}

	const size_t Actor::getArmatureIndex() const
	{
		return this->armatureIndex.value();
	}

	usls::scene::armature::Armature& Actor::getArmature()
	{
		return App::get().getScene()->getArmature(this->armatureIndex.value());
	}

	usls::scene::mesh::Mesh& Actor::getMesh()
	{
		return App::get().getScene()->getMesh(this->meshIndex.value());
	}

	void Actor::animate(std::string animationName)
	{
		if (this->armatureIndex)
		{
			this->getArmature().setCurrentAnimation(animationName);
		}
	}

}