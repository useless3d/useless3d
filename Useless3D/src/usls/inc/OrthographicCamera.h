#pragma once

#include "Camera.h"

namespace usls
{
    class OrthographicCamera : public Camera
    {
    private:
        void updateProjectionMatrix();

        const float pixelsPerUnit;

    public:
        OrthographicCamera(const glm::vec2* screenSize, bool fixed, float nearPlane, float farPlane, float pixelsPerUnit);
    };
}