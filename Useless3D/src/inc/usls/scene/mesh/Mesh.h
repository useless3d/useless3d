#pragma once

#include <vector>
#include <string>
#include <optional>
#include <memory>

#include "glm/glm.hpp"

#include "usls/scene/Shader.h"
#include "usls/scene/camera/Camera.h"
#include "usls/scene/mesh/Vertex.h"
#include "usls/scene/mesh/Texture.h"
#include "usls/scene/mesh/Renderable.h"


namespace usls
{
    class Mesh 
    {

    private:
        std::string                 name;
        std::vector<Vertex>			vertices;
        std::vector<unsigned int>   indices;
        std::optional<std::unique_ptr<Renderable>> renderable;

    public:
        Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices);

        void                                makeRenderable(Texture texture);
        const std::string                   getTexturePath() const;

        const std::string                   getName() const;
        const std::vector<Vertex>&			getVertices() const;
        const std::vector<unsigned int>&	getIndices() const;
        

        const bool                          isRenderable() const;

        
        void                                draw(Shader* shader, Camera* camera, glm::mat4 modelMatrix);



    };
}