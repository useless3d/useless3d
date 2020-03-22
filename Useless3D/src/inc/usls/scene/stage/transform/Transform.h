#pragma once

#include "glm/glm.hpp"

#include "usls/scene/stage/transform/Rotation.h"

namespace usls
{
    class Transform
    {
    private:
        glm::vec3	translation = glm::vec3(0.0f, 0.0f, 0.0f);
        Rotation	rotation;
        glm::vec3	scale = glm::vec3(1.0f, 1.0f, 1.0f);

    public:
                    Transform();
                    Transform(glm::vec3 t, Rotation r, glm::vec3 s);
        void		setTranslation(glm::vec3 translation);
        void		setRotation(float angle, glm::vec3 axis);
        void		setScale(glm::vec3 scale);
        glm::vec3   getTranslation();
        Rotation    getRotation();
        glm::vec3   getScale();
        glm::mat4   getMatrix();
        void        print();
    };
}