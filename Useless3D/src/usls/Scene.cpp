#include "inc/Scene.h"

namespace usls
{
    std::optional<std::unique_ptr<Stage>> Scene::stage;


    Scene::Scene() {};
    Scene::~Scene() {};

    void Scene::setStage(std::string file)
    {
        Scene::stage = std::make_unique<Stage>(file);
    }

}