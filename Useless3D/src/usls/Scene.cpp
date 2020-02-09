#include "inc/Scene.h"

namespace usls
{
    //std::optional<std::unique_ptr<Stage>> Scene::stage;


    Scene::Scene() {};
    Scene::~Scene() {};

    void Scene::setStage(std::string file)
    {
        this->stage = std::make_unique<Stage>(file);
    }

    Stage* Scene::getStage()
    {
        if (this->stage) 
        {
            return this->stage->get();
        }
        else
        {
            return nullptr;
        }
    }

    void Scene::draw()
    {

    }

}