#include <iostream>



#include "usls/App.h"
#include "usls/scene/stage/Actor.h"


namespace usls::scene::stage
{
    Actor::Actor(std::string name, Transform t) :
        name(name),
        deleted(false),
		visible(true),
		dynamic(false),
        transform(t) 
    {}

	void Actor::setDynamic(bool dynamic)
	{
		this->dynamic = dynamic;
	}

	Actor Actor::cleanCopy(std::string newName)
	{
		auto newActor = *this;
		newActor.setName(newName);

		// Clear parents and children
		newActor.parentActor = std::nullopt;
		newActor.parentActorBone = std::nullopt;
		newActor.childActors.clear();

		return newActor;
	}

	void Actor::setName(std::string newName)
	{
		this->name = newName;
	}

	const glm::vec3& Actor::getTranslation()
	{
		return this->transform.getTranslation();
	}

	const glm::quat& Actor::getRotation()
	{
		return this->transform.getRotation();
	}

	const glm::vec3& Actor::getScale()
	{
		return this->transform.getScale();
	}

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

		return this->parentActor.value()->getTransform().getMatrix() * this->parentActorBone.value()->matrix;
	}

	glm::mat4 Actor::getWorldMatrix()
	{
		// if this actor has no parent, simply return the matrix of it's transform
		if (!this->parentActor)
		{
			return this->transform.getMatrix();
		}

		// if this actor is parented to another actor (an not a bone of that actor)
		if (!this->parentActorBone)
		{
			return this->parentActor.value()->getTransform().getMatrix() * this->transform.getMatrix();
		}

		return this->parentActor.value()->getTransform().getMatrix() * this->parentActorBone.value()->matrix * this->transform.getMatrix();

	}

	glm::mat4 Actor::getWorldRenderMatrix(float alpha)
	{
		// actor is not dynamic (does not move) so interpolation is not required, simply return it's world matrix
		if (!this->isDynamic() || !this->previousTransform)
		{
			return this->getWorldMatrix();
		}


		auto actorMatrix = Transform::interpolateTransforms(this->previousTransform.value(), this->transform, alpha);

		// if this actor has no parent, simply return the matrix of it's transform
		if (!this->parentActor)
		{
			return actorMatrix;
		}

		auto parentActorMatrix = Transform::interpolateTransforms(this->parentActor.value()->getPreviousTransform().value(), this->parentActor.value()->getTransform(), alpha);

		// if this actor is parented to another actor (an not a bone of that actor)
		if (!this->parentActorBone)
		{
			return parentActorMatrix * actorMatrix;
		}

		auto boneMatrix = this->parentActorBone.value()->getRenderMatrix(alpha);

		return parentActorMatrix * boneMatrix * actorMatrix;

	}

	const bool Actor::isDynamic() const
	{
		return this->dynamic;
	}

	void Actor::updatePreviousTransform()
	{
		if (!this->isDeleted() && this->isDynamic())
		{
			this->previousTransform = this->getTransform();
		}
	}

	void Actor::translate(glm::vec3 translation)
	{
		this->getTransform().setTranslation(translation);
	}

	void Actor::rotate(float angle, glm::vec3 axis)
	{
		this->getTransform().setRotation(angle, axis);
	}

	void Actor::rotate(glm::quat rotation)
	{
		this->getTransform().setRotation(rotation);
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
        return this->transform;
    }

	std::optional<Transform>& Actor::getPreviousTransform()
	{
		return this->previousTransform;
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