#include <iostream>

#include "glm/gtc/matrix_transform.hpp"

#include "usls/scene/stage/transform/Transform.h"



namespace usls
{

    Transform::Transform() :
        translation(glm::vec3(0.0f, 0.0f, 0.0f)),
        scale(glm::vec3(1.0f, 1.0f, 1.0f))
    {}

    Transform::Transform(glm::vec3 t, Rotation r, glm::vec3 s) :
        translation(t), 
        rotation(r), 
        scale(s){}   

    void Transform::print()
    {
        std::cout << "T:(" << this->translation.x << "," << this->translation.y << "," << this->translation.z << ")\n";
        std::cout << "R-Axis:(" << this->getRotation().axis.x << "," << this->getRotation().axis.y << "," << this->getRotation().axis.z << ") R-Angle:" << this->getRotation().angle << "\n";
        std::cout << "S:(" << this->scale.x << "," << this->scale.y << "," << this->scale.z << ")\n";
        std::cout << "---------------------------------\n";
    }

    void Transform::setTranslation(glm::vec3 translation) 
    {
        this->translation = translation;
    }

    void Transform::setRotation(float angle, glm::vec3 axis)
    {
        this->rotation.angle = angle;
        this->rotation.axis = axis;
    }

    void Transform::setScale(glm::vec3 scale)
    {
        this->scale = scale;
    }

    glm::vec3 Transform::getTranslation()
    {
        return this->translation;
    }

    Rotation Transform::getRotation()
    {
        return this->rotation;
    }

    glm::vec3 Transform::getScale()
    {
        return this->scale;
    }

    const glm::mat4 Transform::getMatrix() const
    {
        glm::mat4 m = glm::mat4(1.0f);
        m = glm::translate(m, this->translation);
        m = glm::rotate(m, glm::radians(this->rotation.angle), this->rotation.axis);
        m = glm::scale(m, this->scale);
        return m;
    }


}