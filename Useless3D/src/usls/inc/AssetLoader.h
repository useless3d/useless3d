#pragma once

#include <string>
#include "Stage.h"
#include <functional>
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace usls
{
    class AssetLoader
    {
    private:
        static std::string currentAssetDirectory;
        static std::string pathWithoutFilename(std::string filePath);
        static const aiScene* loadScene(std::string file);
        static void processNode(aiNode* node, const aiScene* scene, std::function<void(aiNode* node, Mesh* mesh)> cb);
    public:
        static void loadStage(std::string file, Stage* stage);
        
        
    };
}