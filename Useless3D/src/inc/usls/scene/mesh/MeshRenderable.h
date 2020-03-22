#pragma once

#include <vector>


#include "usls/scene/Shader.h"
#include "usls/scene/stage/Camera.h"
#include "usls/scene/mesh/MeshVertex.h"
#include "usls/scene/mesh/MeshTexture.h"

namespace usls
{
    class MeshRenderable
    {
    private:
        MeshTexture	    texture;
        unsigned int	VAO;
        unsigned int	VBO;
        unsigned int    EBO;
        unsigned int    indiceCount;

        void            loadTexture();
        void            sendToGPU(const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices);

    public:
        MeshRenderable(const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices, MeshTexture texture);
        ~MeshRenderable();
        MeshRenderable(MeshRenderable&&) = default;

        const MeshTexture&  getTexture() const;

        void            draw(Shader* shader, Camera* camera, glm::mat4 modelMatrix);

    };
}