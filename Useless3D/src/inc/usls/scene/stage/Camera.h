#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace usls
{
    // using this enum to avoid polymorphism where it is not really necessary
    enum CameraType {
        ORTHOGRAPHIC,
        PERSPECTIVE
    };

    class Camera
    {        
    private:
        std::string             name;
        CameraType              type;
        float                   fovScale;
        const glm::vec2*        screenSize;
        float                   nearPlane;
        float                   farPlane;

        glm::vec3			    position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3			    lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3			    up = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4			    viewMatrix = glm::mat4(1.0f); // initialized as identity matrix
        glm::mat4			    projectionMatrix = glm::mat4(1.0f); // initialized as identity matrix

        void                    updateViewMatrix();
        void                    updateProjectionMatrix();

    public:
        Camera(CameraType type, bool fixed, float nearPlane, float farPlane, float fovScale);

        bool                    fixed;
        void                    update();
        glm::mat4               getViewMatrix();
        glm::mat4               getProjectionMatrix();

        glm::vec3               getPosition();

        void                    setPosition(glm::vec3 p);
        void                    setLookAt(glm::vec3 la);
    

    };
}