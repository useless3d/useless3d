#pragma once

#include "usls/scene/camera/Camera.h"

namespace usls
{
    class PerspectiveCamera : public Camera
    {
    private:
        float				fov;

        void                updateProjectionMatrix();

    public:
        PerspectiveCamera(bool fixed, float nearPlane, float farPlane, float fov);
    };
}