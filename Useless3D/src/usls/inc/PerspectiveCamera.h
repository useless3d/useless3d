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
        PerspectiveCamera(const glm::vec2* screenSize, bool fixed, float nearPlane, float farPlane, float fov);
    };
}