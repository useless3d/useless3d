#include "inc/Scene.h"
#include "inc/Mesh.h"
#include "inc/Camera.h"

namespace usls
{
    Scene::Scene()
    {
        
    };

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
    void Scene::addStage(std::string name, std::string file, ProjectionType pType, ViewSpace vSpace)
    {
        this->stages[name] = new Stage(file, pType, vSpace);
    }

    int Scene::getStageCount()
    {
        return this->stages.size();
    }

    int Scene::getStagePropCount(std::string sName)
    {
        return this->stages[sName]->getNumProps();
    }

    void Scene::clearStages()
    {
        for (auto& [key, val] : this->stages)
        {
            delete val;
        }
        this->stages.clear();
    }





    int Scene::getTotalMeshCount()
    {
        return Mesh::getMeshCount();
    }

    void Scene::draw()
    {
        for (auto& [skey, sval] : this->stages)
        {
            for (auto& p : sval->getProps())
            {



            }
        }
    }

    void Scene::clear()
    {
        this->clearStages();
        Mesh::clearMeshes();
    }

}