#include <iostream>

#include "usls/App.h"
#include "usls/scene/Scene.h"
#include "usls/scene/camera/PerspectiveCamera.h"
#include "usls/scene/camera/OrthographicCamera.h"


namespace usls
{
    Scene::Scene()
    {
        if (!App::get().config.HEADLESS)
        {
            // initialize the default shader
            this->shaders["default"] = std::move(std::make_unique<Shader>(
                App::get().config.SHADER_FILE_PATH, 
                App::get().config.DEFAULT_VERTEX_SHADER, 
                App::get().config.DEFAULT_FRAGMENT_SHADER));
        }
    }

    void Scene::addShader(std::string name, std::string vertName, std::string fragName)
    {
        this->shaders[name] = std::move(std::make_unique<Shader>(
            App::get().config.SHADER_FILE_PATH,
            vertName,
            fragName));
    }

    void Scene::addPerspectiveCamera(std::string name, bool fixed, float nearPlane, float farPlane, float fov)
    {
        this->cameras[name] = std::move(std::make_unique<PerspectiveCamera>(
            fixed,
            nearPlane,
            farPlane,
            fov
        ));
    }

    void Scene::addOrthographicCamera(std::string name, bool fixed, float nearPlane, float farPlane, float scale)
    {
        this->cameras[name] = std::move(std::make_unique<OrthographicCamera>(
            fixed,
            nearPlane,
            farPlane,
            scale));
    }

    void Scene::addStage(std::string name, std::string cameraName)
    {
        this->stages[name] = std::move(std::make_unique<Stage>(this->cameras[cameraName].get()));
    }

    void Scene::addStage(std::string name)
    {
        this->stages[name] = std::move(std::make_unique<Stage>());
    }

    void Scene::addActor(std::string stageName, std::string actorFile)
    {
        this->currentAssetDirectory = actorFile.substr(0, actorFile.find_last_of('/'));

        Assimp::Importer importer;
        const aiScene* aiScene;

        this->processNode(aiScene->mRootNode, aiScene);

    }


    void Scene::getAssimpScene(std::string filePath, Assimp::Importer &importer, const aiScene* &scene) const
    {
        scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::string errorMessage = importer.GetErrorString();
            std::cout << "ERROR::ASSIMP::" << errorMessage << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }
    }

    void Scene::processNode(aiNode* node, const aiScene* scene)
    {

    }


    ///*
    //* Add a headless stage
    //*/
    //void Scene::addStage(std::string stageName)
    //{
    //    auto newStage = std::make_unique<Stage>(stageName);
    //    this->stages.push_back(std::move(newStage));
    //}

    ///*
    //* Add a NON-headless stage. Since camera is passed we know the user intends for this to be a renderable stage.
    //* However this will be overwritten if the state of the app is set to headless.
    //*/
    //void Scene::addStage(std::string stageName, std::unique_ptr<Camera> camera)
    //{
    //    auto newStage = std::make_unique<Stage>(stageName, std::move(camera));
    //    this->stages.push_back(std::move(newStage));
    //}

    //void Scene::draw()
    //{
    //    // TODO: Interpolation of all Stage Actors (this will require a fair amout of restructuring of how
    //    // we are currently drawing renderables)

    //    // Draw all stages in order they were created (layered)
    //    for (auto& s : this->stages)
    //    {
    //        s->draw(&this->shader.value());
    //    }

    //}

}