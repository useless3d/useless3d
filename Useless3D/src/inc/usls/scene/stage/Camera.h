#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace usls::scene::stage
{
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
        const glm::ivec2*       screenSize;
        float                   nearPlane;
        float                   farPlane;
        glm::vec3			    position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3			    lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3			    up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4			    viewMatrix = glm::mat4(1.0f);
        glm::mat4			    projectionMatrix = glm::mat4(1.0f);
        void                    updateViewMatrix();
        void                    updateProjectionMatrix();

    public:
								Camera(CameraType type, bool fixed, float nearPlane, float farPlane, float fovScale);
        bool                    fixed;
        void                    update();
        glm::mat4               getViewMatrix();
        glm::mat4               getProjectionMatrix();
        glm::vec3               getPosition();
        void                    setPosition(float x, float y, float z);
        void                    setLookAt(float x, float y, float z);

    };
}