#pragma once

#include <vector>


#include "usls/scene/Shader.h"
#include "usls/scene/stage/camera/Camera.h"
#include "usls/scene/stage/mesh/Vertex.h"
#include "usls/scene/stage/mesh/Texture.h"

namespace usls
{
    class Renderable
    {
    private:
        Texture			texture;
        unsigned int	VAO;
        unsigned int	VBO;
        unsigned int    EBO;
        unsigned int    indiceCount;

        void            loadTexture();
        void            sendToGPU(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    public:
        Renderable(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture texture);
        ~Renderable();

        const Texture&  getTexture() const;

        void            draw(Shader* shader, Camera* camera, glm::mat4 modelMatrix);

    };
}