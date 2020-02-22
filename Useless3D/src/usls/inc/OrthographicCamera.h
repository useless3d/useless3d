#pragma once

#include "Camera.h"

namespace usls
{
    class OrthographicCamera : public Camera
    {
    private:
        void updateProjectionMatrix();

    public:
        OrthographicCamera(const glm::vec2* screenSize, bool fixed, float nearPlane, float farPlane);
    };
}