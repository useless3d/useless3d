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
#include "usls/scene/Stage.h"
#include "usls/scene/transformable/Transformable.h"
#include "usls/scene/Shader.h"
#include "usls/scene/camera/Camera.h"
#include "usls/scene/Actor.h"


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

    protected:

        std::vector<std::unique_ptr<Mesh>>                  meshes;
        std::map<std::string, std::unique_ptr<Shader>>      shaders;
        std::map<std::string, std::unique_ptr<Camera>>      cameras;
        std::map<std::string, std::unique_ptr<Stage>>       stages;
        std::map<std::string, std::unique_ptr<Actor>>       actors;

        void                addShader(std::string name, std::string vertName, std::string fragName);
        void                addPerspectiveCamera(std::string name, bool fixed, float nearPlane, float farPlane, float fov);
        void                addOrthographicCamera(std::string name, bool fixed, float nearPlane, float farPlane, float scale);

        void                addStage(std::string name, std::string cameraName);
        void                addStage(std::string name); // for use in headless state

        void                addActor(std::string stageName, std::string actorFile, std::string shader = "default");

        

    public:
        bool                loaded = false;

                            Scene();
        void                draw();         

        virtual void        load() = 0;
        virtual void        loop() = 0;
        virtual void        end() = 0;
        

    };

}