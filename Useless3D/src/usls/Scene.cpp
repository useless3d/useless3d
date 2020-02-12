#include "inc/Scene.h"
#include "inc/Mesh.h"

namespace usls
{
    Scene::Scene() {};

    Scene* Scene::instance = 0;

    Scene* Scene::get()
    {
        if (instance == 0)
        {
            instance = new Scene();
        }
        return instance;
    }


    /* Functionality for operating on stage
    ************************************************************************/
    int Scene::getStagePropCount()
    {
        if (this->stage) {
            return this->stage.value()->getNumProps();
        }
        else
        {
            return 0;
        }
    }

    void Scene::setStage(std::string file)
    {
        this->stage = new Stage(file);
    }

    void Scene::clearStage()
    {
        this->stage.reset();
    }


    int Scene::getTotalMeshCount()
    {
        return Mesh::getMeshCount();
    }



    void Scene::draw()
    {

    }

    void Scene::clear()
    {
        if (this->stage)
        {
            this->clearStage();
        }
        Mesh::clearMeshes();
    }

}