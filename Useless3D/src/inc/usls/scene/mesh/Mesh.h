#pragma once

#include <vector>
#include <string>
#include <optional>
#include <memory>

#include "glm/glm.hpp"

#include "usls/scene/Shader.h"
#include "usls/scene/stage/Camera.h"
#include "usls/scene/mesh/MeshVertex.h"
#include "usls/scene/mesh/MeshTexture.h"
#include "usls/scene/mesh/MeshRenderable.h"


namespace usls
{
    class Mesh 
    {

    private:
        std::string                         name;
        std::vector<MeshVertex>	            vertices;
        std::vector<unsigned int>           indices;
        std::optional<int>                  meshRenderableIndex;

    public:
        Mesh(std::string name, std::vector<MeshVertex> vertices, std::vector<unsigned int> indices);

        void                                setMeshRenderableIndex(int index);

        const std::string                   getName() const;
        const std::vector<MeshVertex>&		getVertices() const;
        const std::vector<unsigned int>&	getIndices() const;
        const bool                          isRenderable() const;




    };
}