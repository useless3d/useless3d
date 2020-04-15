#pragma once

#include <optional>
#include <string>

#include "glm/glm.hpp"

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/stage/Transform.h"


namespace usls::scene::stage
{
    class Actor
    {
    private:
        bool						deleted;
        std::string					name;
        Transform					transform;

        std::optional<size_t>		shaderIndex;
        std::optional<size_t>		meshIndex;
        std::optional<size_t>		textureIndex;
		std::optional<size_t>		armatureIndex;
        
        std::optional<std::pair<size_t, size_t>> renderCommand;

    public:
        Actor(std::string name, Transform t);

        void									setMeshIndex(size_t i);
        void									setShaderIndex(size_t i);
        void									setTextureIndex(size_t i);
		void									setArmatureIndex(size_t i);

        const std::string						getName() const;
        const std::optional<size_t>&			getShaderIndex() const;
        const std::optional<size_t>&			getMeshIndex() const;
        const std::optional<size_t>&			getTextureIndex() const;
        void									addRenderCommand(std::pair<size_t, size_t> cmd);
        const std::pair<size_t, size_t>&		getRenderCommand() const;
        void									setDeleted(bool d);
        const bool								isDeleted() const;
		const bool								isAnimated() const;
		const size_t							getArmatureIndex() const;

		void									animate(std::string animationName);

        Transform&								getTransform();

    };
}