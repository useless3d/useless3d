#include "inc/AssetLoader.h"
#include "inc/Logger.h"

#include <iostream>

namespace usls
{
    std::string AssetLoader::currentAssetDirectory = "";
    

    void AssetLoader::loadStage(std::string file, Stage* stage)
    {
        const aiScene* scene = loadScene(file);
        currentAssetDirectory = pathWithoutFilename(file);
        processNode(scene->mRootNode, scene, [&](aiNode* node, Mesh* mesh) {
            
            //std::cout << "Well...we're here\n";
            //std::cout << stage->getNumProps() + "\n";

        });
    }

    const aiScene* AssetLoader::loadScene(std::string file)
    {

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            if (Logger::isEnabled()) {
                std::string errorMessage = importer.GetErrorString();
                Logger::log("ERROR::ASSIMP::" + errorMessage);
            }
            exit(EXIT_FAILURE);
        }

        return scene;

    }

    std::string AssetLoader::pathWithoutFilename(std::string filePath)
    {
        return filePath.substr(0, filePath.find_last_of('/'));
    }

    void AssetLoader::processNode(aiNode* node, const aiScene* scene, std::function<void(aiNode* node, Mesh* mesh)> cb)
    {
        // For debugging
        //std::cout << "node:";
        //std::cout << node->mName.C_Str();
        //std::cout << " parent:";
        //if (node->mParent != NULL) {
        //    std::cout << node->mParent->mName.C_Str();
        //    std::cout << "\n";
        //}
        //else {
        //    std::cout << "ROOT\n";
        //}

        // If node has more than one mesh, log an error and exit (as I cannot think of a reason
        // why a node would have more than one mesh at this time, therefore if we ever receive
        // an error here we can re-examine our thought process)
        // Well this answers my question: https://github.com/assimp/assimp/issues/314 however i'm
        // not implementing support for multiple meshes per node until a reason is brought to light
        if (node->mNumMeshes > 1) 
        {
            if (Logger::isEnabled()) 
            {
                std::string nodeName = node->mName.C_Str();
                Logger::log("AssetLoader ERROR: The following node contains more than one mesh: " + nodeName);
            }
            exit(EXIT_FAILURE);
        }
        if (node->mNumMeshes == 1) // process mesh
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[0]];
            std::cout << mesh->mName.C_Str();
            std::cout << "\n";

            // process mesh



            // asset specific logic
            //cb(node, );

        }

        // Do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene, cb);
        }



    }

}