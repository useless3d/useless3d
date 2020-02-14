#include "inc/Scene.h"
#include "inc/Mesh.h"
#include "inc/Camera.h"
#include "inc/Logger.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace usls
{
    Scene::Scene() :
        shader(Shader("Useless3D/src/usls/shaders", "default.vert", "default.frag"))
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
        
        glEnable(GL_DEPTH_TEST);

        // Select a color to clear the screen with and clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->shader.use();

        for (auto& [skey, sval] : this->stages)
        {
         
            std::cout << "------------\n";
            for (auto& p : sval->getProps())
            {

                
                //std::cout << p.getTranslation().x << "," << p.getTranslation().y << "," << p.getTranslation().z << "\n";
                
                //std::cout << glm::to_string(Camera::get()->getPerspectiveProjectionMatrix() * Camera::get()->getViewMatrix() * p.getMatrix()) << std::endl;

                this->shader.setMat4("mvp", Camera::get()->getPerspectiveProjectionMatrix() * Camera::get()->getViewMatrix() * p.getMatrix());



                // activate proper texture unit before binding
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, p.getMesh()->getTexture().id);

                //std::cout << p.getMesh()->getIndices().size() << "\n";

                this->shader.setInt("texture1", 0);

                // draw mesh
                glBindVertexArray(p.getMesh()->getVAO());
                glDrawElements(GL_TRIANGLES, p.getMesh()->getIndices().size(), GL_UNSIGNED_INT, 0);

                // set everything back to defaults
                glBindVertexArray(0);

                

            }
            std::cout << "------------\n";
        }
    }

    void Scene::clear()
    {
        this->clearStages();
        Mesh::clearMeshes();
    }

}