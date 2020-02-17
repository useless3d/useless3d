#pragma once

#include <vector>
#include <string>
#include <optional>
#include <memory>
#include <functional>

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
        bool                            headless;
        std::string                     name;
        std::vector<Prop>               props;
        std::optional<ProjectionType>   pType;
        std::optional<ViewSpace>        vSpace;
        std::vector<std::unique_ptr<Mesh>> meshes;
        std::string                     currentAssetDirectory = "";

        void                            getAssimpScene(std::string filePath, Assimp::Importer &importer, const aiScene* &scene) const;
        void                            processNode(aiNode* node, const aiScene* scene, std::function<void(aiNode* node, Mesh* mesh)> cb);
        Mesh*                           processMesh(aiNode* node, const aiScene* scene);

    public:
        Stage(std::string name);
        Stage(std::string name, ProjectionType pType, ViewSpace vSpace);
        ~Stage();
        void                addProp(std::string filePath);
  

    };
}