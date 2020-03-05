#pragma once

#include "usls/scene/stage/camera/Camera.h"

namespace usls
{
    class OrthographicCamera : public Camera
    {
    private:
        void updateProjectionMatrix();

        const float scale;

    public:
        OrthographicCamera(bool fixed, float nearPlane, float farPlane, float scale);
    };
}