#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <functional>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/stage/Stage.h"
#include "usls/scene/stage/transformable/Transformable.h"
#include "usls/scene/Shader.h"
#include "usls/scene/stage/Camera.h"


namespace usls 
{

    class Scene
    {
    private:
        std::string         currentActorFile = "";
        std::string         currentAssetDirectory = "";
        Mesh*               currentMeshPtr;
        Transformable       currentTransformable;
        std::string         currentStageName = "";

        void                getAssimpScene(std::string filePath, Assimp::Importer &importer, const aiScene* &scene) const;
        void                processNode(aiNode* node, const aiScene* scene);
        void                processTransformable(aiNode* node);
        void                processMesh(aiNode* node, const aiScene* scene);
        std::string         generateUniqueActorName(std::string name);
        
        std::function<void(Actor* a)> sendToShader;


        std::vector<Shader>                         shaders;
        std::vector<Stage>                          stages;
        std::vector<Mesh>                           meshes;
        

        



    protected:
        void                addShader(std::string name, std::string vertName, std::string fragName);
        
        

        void                addStage(int id);
        Stage&              getStage(int id);

        void                addActors(Stage& stage, std::string actorFile, std::string shader = "default");

        

    public:
        bool                loaded = false;

                            Scene();
        void                draw();         

        virtual void        load() = 0;
        virtual void        loop() = 0;
        virtual void        end() = 0;
        

    };

}