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

	void Actor::setActiveBones(std::vector<std::pair<size_t, std::string>> activeBones)
	{
		this->activeBones = activeBones;
	}

	const std::optional<std::vector<std::pair<size_t, std::string>>>& Actor::getActiveBones() const
	{
		return this->activeBones;
	}

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

    Transform& Actor::getTransform()
    {
		if (this->isAnimated())
		{
			return this->armature->getTransform();
		}
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
		if (this->armature) 
		{
			return true;
		}
		return false;
	}

	void Actor::setArmature(usls::scene::armature::Armature& arm)
	{
		this->armature = arm;
	}

	usls::scene::armature::Armature& Actor::getArmature()
	{
		return this->armature.value();
	}

	usls::scene::mesh::Mesh& Actor::getMesh()
	{
		return App::get().getScene()->getMesh(this->meshIndex.value());
	}

	void Actor::animate(std::string animationName)
	{
		if (this->armature)
		{
			this->getArmature().setCurrentAnimation(animationName);
		}
	}

}