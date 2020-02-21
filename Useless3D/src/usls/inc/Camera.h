#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace usls
{
    class Camera
    {
    public:
        enum Projection
        {
            PERSPECTIVE,
            ORTHOGRAPHIC
        };
        enum ViewSpace
        {
            VIEW,
            WORLD
        };

        Camera(const glm::vec2* screenSize, Projection projectionType, ViewSpace viewSpace, float nearPlane, float farPlane);
        ~Camera();

        void        update();
        glm::mat4   getViewMatrix();
        glm::mat4   getProjectionMatrix();

        void        setPosition(glm::vec3 p);
        void        setLookAt(glm::vec3 la);
        
    protected:
        const glm::vec2* 	screenSize;
        float               nearPlane;
        float               farPlane;

        glm::vec3			position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3			lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3			up = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4			viewMatrix = glm::mat4(1.0f); // initialized as identity matrix
        glm::mat4			projectionMatrix = glm::mat4(1.0f); // initialized as identity matrix

        Projection          projectionType;
        ViewSpace           viewSpace;

        void                updateViewMatrix();
        virtual void        updateProjectionMatrix() = 0;
    

    };
}