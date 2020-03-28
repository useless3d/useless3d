#pragma once

#include <optional>
#include <string>

#include "glm/glm.hpp"

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/stage/transform/Transform.h"

namespace usls
{
    class Actor
    {
    private:
        bool                    deleted;
        std::string             name;
        Transform               transform;

        std::optional<int>      shaderIndex;
        std::optional<int>      meshIndex;
        std::optional<int>      textureIndex;
        
        std::optional<std::pair<int, int>> renderCommand;

    public:
        Actor(std::string name, Transform t);
        Actor(std::string name, Transform t, int meshIndex);
        Actor(std::string name, Transform t, int meshIndex, int shaderIndex);
        Actor(std::string name, Transform t, int meshIndex, int shaderIndex, int textureIndex);

        const std::string               getName() const;
        const std::optional<int>&       getShaderIndex() const;
        const std::optional<int>&       getMeshIndex() const;
        const std::optional<int>&       getTextureIndex() const;
        void                            addRenderCommand(std::pair<int, int> cmd);
        const std::pair<int, int>&      getRenderCommand() const;
        void                            setDeleted(bool d);
        const bool                      isDeleted() const;

        Transform&                      getTransform();

    };
}