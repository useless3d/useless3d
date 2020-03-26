#include <iostream>

#include "usls/App.h"
#include "usls/scene/Scene.h"
#include "usls/scene/mesh/MeshVertex.h"
#include "usls/scene/mesh/MeshTexture.h"


namespace usls
{
    Scene::Scene() :
        headless(App::get().config.HEADLESS)
    {
        if (!this->headless)
        {
            // initialize the default shader
            App::get().getGPU()->loadShader(
                "default",
                App::get().config.DEFAULT_VERTEX_SHADER, 
                App::get().config.DEFAULT_FRAGMENT_SHADER);
        }
    }

    int Scene::addShader(std::string name, std::string vertName, std::string fragName)
    {
        return App::get().getGPU()->loadShader(name, vertName, fragName);
    }

    int Scene::addStage()
    {
        this->stages.push_back(Stage(this->headless));
        return this->stages.size() - 1;
    }

    Stage& Scene::getStage(int id)
    {
        return this->stages.at(id);
    }

    const std::vector<Mesh>& Scene::getMeshes() const
    {
        return this->meshes;
    }

    unsigned int Scene::addMesh(Mesh m)
    {
        if (!this->headless)
        {
            m.setMeshRenderableIndex(App::get().getGPU()->loadMesh(m)); // Since this is not headless mode, send mesh to the GPU
        }
        this->meshes.push_back(m);
        return this->meshes.size() - 1;
    }

    Mesh& Scene::getMesh(unsigned int index)
    {
        return this->meshes.at(index);
    }


    void Scene::draw()
    {
        for (auto& s : this->stages)
        {
            s.printRenderCommands();

            //int activeShader = -1;
            //int activeMesh = -1;
            //int activeTexture = -1;

            //for (auto& rc : s.getRenderCommands().value())
            //{
            //    if (rc.getShaderIndex() != activeShader)
            //    {
            //        activeShader = rc.getShaderIndex();

            //    }
            //}
            
        }


        std::cin.get();
    }

}