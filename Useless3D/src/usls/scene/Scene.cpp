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
            unsigned int shaderProgramId = App::get().getGPU()->loadShader(
                App::get().config.DEFAULT_VERTEX_SHADER, 
                App::get().config.DEFAULT_FRAGMENT_SHADER);

            this->shaders.push_back(Shader("default", shaderProgramId));
        }
    }

    void Scene::addShader(std::string name, std::string vertName, std::string fragName)
    {
        unsigned int shaderProgramId = App::get().getGPU()->loadShader(vertName, fragName);
        this->shaders.push_back(Shader(name, shaderProgramId));
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

    const std::vector<MeshTexture>& Scene::getTextures() const
    {
        return this->textures;
    }

    unsigned int Scene::addMesh(Mesh m)
    {
        this->meshes.push_back(m);
        return this->meshes.size() - 1;
    }

    Mesh& Scene::getMesh(unsigned int index)
    {
        return this->meshes.at(index);
    }

    MeshTexture& Scene::getTexture(unsigned int index)
    {
        return this->textures.at(index);
    }

    unsigned int Scene::addTexture(MeshTexture t)
    {
        this->textures.push_back(t);
        return this->textures.size() - 1;
    }

    void Scene::draw()
    {
        for (auto& s : this->stages)
        {
            //s.printRenderCommands();

            int activeShader = -1;
            int activeMesh = -1;
            int activeTexture = -1;

            for (auto& rc : s.getRenderCommands().value())
            {
                if (rc.getShaderIndex() != activeShader)
                {
                    activeShader = rc.getShaderIndex();

                }
            }
            
        }


        //std::cin.get();
    }

}