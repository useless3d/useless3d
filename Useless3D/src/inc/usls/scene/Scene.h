#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/Stage.h"
#include "usls/scene/Shader.h"
#include "usls/scene/camera/Camera.h"


namespace usls 
{

    class Scene
    {
    private:
        std::string         currentAssetDirectory;

        void                getAssimpScene(std::string filePath, Assimp::Importer &importer, const aiScene* &scene) const;
        void                processNode(scene->mRootNode, aiScene);

    protected:
        std::vector<std::unique_ptr<Mesh>>                  meshes;
        std::map<std::string, std::unique_ptr<Shader>>      shaders;
        std::map<std::string, std::unique_ptr<Camera>>      cameras;
        std::map<std::string, std::unique_ptr<Stage>>       stages;

        void                addShader(std::string name, std::string vertName, std::string fragName);
        void                addPerspectiveCamera(std::string name, bool fixed, float nearPlane, float farPlane, float fov);
        void                addOrthographicCamera(std::string name, bool fixed, float nearPlane, float farPlane, float scale);

        void                addStage(std::string name, std::string cameraName);
        void                addStage(std::string name); // for use in headless state

        void                addActor(std::string stageName, std::string actorFile);

        

    public:
        bool                loaded = false;

                            Scene();
        void                draw();         

        virtual void        load() = 0;
        virtual void        loop() = 0;
        virtual void        end() = 0;
        

    };

}