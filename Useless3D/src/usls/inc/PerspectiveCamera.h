#pragma once

#include "Camera.h"

namespace usls
{
    class PerspectiveCamera : public Camera
    {
    private:
        float				fov;

        void                updateProjectionMatrix();

    public:
        PerspectiveCamera(const glm::vec2* screenSize, Projection projectionType, 
            ViewSpace viewSpace, float nearPlane, float farPlane, float fov);
        ~PerspectiveCamera();
    };
}