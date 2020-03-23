#pragma once

#include <vector>
#include <string>
#include <functional>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/stage/Stage.h"
#include "usls/scene/stage/transform/Transform.h"
#include "usls/scene/Shader.h"


namespace usls 
{

    class ActorLoader
    {
    private:
        bool                headless;
        Stage*              currentStage;
        std::string         currentActorFile;
        std::string         currentAssetDirectory;
        Transform           currentTransform;
        int                 currentMeshIndex;
        int                 currentMeshTextureIndex;

        void                getAssimpScene(std::string filePath, Assimp::Importer &importer, const aiScene* &scene) const;
        void                processNode(aiNode* node, const aiScene* scene);
        void                processTransformable(aiNode* node);
        void                processMesh(aiNode* node, const aiScene* scene);
        std::string         generateUniqueActorName(std::string name);

    public:
                            ActorLoader(Stage* stage, std::string actorFile);
        std::optional<std::function<int(std::string actorName)>> findShaderId;
        void                execute();


    };

}