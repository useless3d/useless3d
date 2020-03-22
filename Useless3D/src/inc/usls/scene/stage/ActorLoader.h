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
        int                 currentMeshIndex;
        Transform           currentTransform;

        void                getAssimpScene(std::string filePath, Assimp::Importer &importer, const aiScene* &scene) const;
        void                processNode(aiNode* node, const aiScene* scene);
        void                processTransformable(aiNode* node);
        void                processMesh(aiNode* node, const aiScene* scene);
        std::string         generateUniqueActorName(std::string name);

        std::function<void(Actor* a)> sendToShader;

    public:
                            ActorLoader(Stage* stage, std::string actorFile);
        void                execute();


    };

}