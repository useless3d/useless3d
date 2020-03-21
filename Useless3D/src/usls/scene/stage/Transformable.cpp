#include <iostream>

#include "glm/gtc/matrix_transform.hpp"

#include "usls/scene/transformable/Transformable.h"



namespace usls
{

    Transformable::Transformable() 
    {
    
    }
    
    Transformable::Transformable(Transformable& t) :
        translation(t.getTranslation()),
        rotation(t.getRotation()),
        scale(t.getScale())
    {

    }

    Transformable::Transformable(glm::vec3 t, Rotation r, glm::vec3 s) : 
        translation(t), 
        rotation(r), 
        scale(s)
    {
    
    }   

    void Transformable::printTransformable()
    {
        std::cout << "T:(" << this->translation.x << "," << this->translation.y << "," << this->translation.z << ")\n";
        std::cout << "R-Axis:(" << this->getRotation().axis.x << "," << this->getRotation().axis.y << "," << this->getRotation().axis.z << ") R-Angle:" << this->getRotation().angle << "\n";
        std::cout << "S:(" << this->scale.x << "," << this->scale.y << "," << this->scale.z << ")\n";
        std::cout << "---------------------------------\n";
    }

    void Transformable::setTranslation(glm::vec3 translation) 
    {
        this->translation = translation;
    }

    void Transformable::setRotation(float angle, glm::vec3 axis) 
    {
        this->rotation.angle = angle;
        this->rotation.axis = axis;
    }

    void Transformable::setScale(glm::vec3 scale) 
    {
        this->scale = scale;
    }

    glm::vec3 Transformable::getTranslation()
    {
        return this->translation;
    }

    Rotation Transformable::getRotation()
    {
        return this->rotation;
    }

    glm::vec3 Transformable::getScale()
    {
        return this->scale;
    }

    glm::mat4 Transformable::getTransformMatrix()
    {
        glm::mat4 m = glm::mat4(1.0f);
        m = glm::translate(m, this->translation);
        m = glm::rotate(m, glm::radians(this->rotation.angle), this->rotation.axis);
        m = glm::scale(m, this->scale);
        return m;
    }


}