#include <iostream>

#include "usls/App.h"
#include "usls/scene/stage/Actor.h"

namespace usls::scene::stage
{
    Actor::Actor(std::string name, Transform t) :
        name(name),
        deleted(false),
		visible(true),
        transform(t) 
    {}

	std::optional<glm::mat4> Actor::getParentMatrix()
	{
		if (!this->parentActor)
		{
			return std::nullopt;
		}

		if (!this->parentActorBone)
		{
			return this->parentActor.value()->getTransform().getMatrix();
		}

		return this->parentActorBone.value()->matrix;
	}

	glm::mat4 Actor::getWorldMatrix()
	{
		// if this actor has no parent, simply return the matrix of it's transform
		if (!this->parentActor)
		{
			return this->getTransform().getMatrix();
		}

		// if this actor is parented to another actor (an not a bone of that actor)
		if (!this->parentActorBone)
		{
			return this->parentActor.value()->getTransform().getMatrix() * this->getTransform().getMatrix();
		}

		return this->parentActorBone.value()->matrix * this->getTransform().getMatrix();

	}

	void Actor::translate(glm::vec3 translation)
	{
		this->getTransform().setTranslation(translation);
	}

	void Actor::rotate(float angle, glm::vec3 axis)
	{
		this->getTransform().setRotation(angle, axis);
	}

	void Actor::scale(glm::vec3 scale)
	{
		this->getTransform().setScale(scale);
	}

	void Actor::setParentActor(Actor* a)
	{
		this->parentActor = a;
	}

	void Actor::setParentActorBone(usls::scene::armature::Bone* b)
	{
		this->parentActorBone = b;
	}

	void Actor::addChildActor(Actor* a)
	{
		this->childActors.push_back(a);
	}

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

	const bool Actor::isVisible() const
	{
		return this->visible;
	}

	void Actor::setVisible(bool v)
	{
		this->visible = v;
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