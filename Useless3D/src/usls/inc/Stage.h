#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Prop.h"

namespace usls
{
    enum ProjectionType
    {
        PERSPECTIVE,
        ORTHOGRAPHIC
    };

    enum ViewSpace
    {
        VIEW,
        WORLD
    };

    class Stage
    {
    private:
        std::string             name;
        std::vector<Prop>       props;
        ProjectionType          pType;
        ViewSpace               vSpace;

        void                    getAssimpScene(std::string filePath, Assimp::Importer &importer, const aiScene* &scene);

    public:
        Stage(std::string name, ProjectionType pType, ViewSpace vSpace);
        ~Stage();
        void                addProps(std::string filePath);
  

    };
}