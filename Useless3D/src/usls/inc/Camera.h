#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace usls
{
    class Camera
    {
    private:
        Camera(glm::vec2* screenSize);
        static Camera* instance;

        glm::vec2*			screenSize;
        float				fov = 45.0f;

        glm::vec3			position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3			direction = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3			up = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4			viewMatrix = glm::mat4(1.0f); // initialized as identity matrix
        glm::mat4			perspectiveProjectionMatrix = glm::mat4(1.0f); // initialized as identity matrix

    public:
        static Camera* init(glm::vec2* screenSize);
        static Camera* get();
        
        void        setFov(float fov);
        float       getFov();

        void	    setDirection(glm::vec3 direction);
        void	    setPosition(glm::vec3 position);

        glm::vec3   getDirection();
        glm::vec3   getPosition();

        void        updateViewMatrix();
        void        updatePerspectiveProjectionMatrix();

        glm::mat4   getViewMatrix();
        glm::mat4   getPerspectiveProjectionMatrix();


    };
}