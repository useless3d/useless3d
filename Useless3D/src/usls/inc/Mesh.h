#pragma once

#include <vector>
#include <string>
#include <optional>
#include "Vertex.h"
#include "Texture.h"
#include "Renderable.h"

namespace usls
{
    class Mesh 
    {

    private:
        std::string                 name;
        std::vector<Vertex>			vertices;
        std::vector<unsigned int>   indices;
        std::optional<Renderable>   renderable;

    public:
        ~Mesh();
        Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices);

        void                                makeRenderable(Texture texture);
        const Renderable&                   getRenderable() const;

        const std::string                   getName() const;
        const std::vector<Vertex>&			getVertices() const;
        const std::vector<unsigned int>&	getIndices() const;

        //const unsigned int&         getVAO();

    };
}