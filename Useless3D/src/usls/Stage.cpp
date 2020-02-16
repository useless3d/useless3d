#include "inc/Stage.h"
#include "inc/Logger.h"

namespace usls
{

    Stage::Stage(std::string name, ProjectionType pType, ViewSpace vSpace) :
        name(name),
        pType(pType),
        vSpace(vSpace)
    {
        //AssetLoader::loadStage(file, this);
    }
    Stage::~Stage() 
    {
        
    }

    void Stage::addProps(std::string filePath)
    {
        Assimp::Importer importer;
        const aiScene* scene;
        this->getAssimpScene(filePath, importer, scene);



    }

    void Stage::getAssimpScene(std::string filePath, Assimp::Importer &importer, const aiScene* &scene)
    {
        scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            if (Logger::isEnabled())
            {
                std::string errorMessage = importer.GetErrorString();
                Logger::log("ERROR::ASSIMP::" + errorMessage);
            }
            exit(EXIT_FAILURE);
        }
    }

}