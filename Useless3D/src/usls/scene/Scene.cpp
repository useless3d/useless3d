#include <iostream>

#include "usls/App.h"
#include "usls/scene/Scene.h"
#include "usls/scene/mesh/MeshVertex.h"
#include "usls/scene/mesh/MeshTexture.h"


namespace usls
{
    Scene::Scene() :
        headless(App::get().config.HEADLESS),
        loaded(false)
    {
        this->stages.reserve(10); // can't see ever needing more than 10 stages (naive, but good enough until it's not)
    }

    Scene::~Scene()
    {
        //std::cout << "Scene Destructor Ran\n";
        App::get().getGPU()->wipe();
    }

    int Scene::addShader(std::string name, std::string vertName, std::string fragName)
    {
        return App::get().getGPU()->loadShader(name, vertName, fragName);
    }

    Stage& Scene::addStage()
    {
        this->stages.push_back(Stage(this->headless));
        return this->getStage(this->stages.size() - 1);
    }

    Stage& Scene::getStage(int index)
    {
        return this->stages.at(index);
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
        GPU& gpu = App::get().getGPU().value();

        //int i = 0;
        //for (auto& mt : gpu.getTextures())
        //{
        //    std::cout << "i:" << i << " " << mt.path << "\n";
        //    i++;
        //}

        for (auto& s : this->stages)
        {
            //s.printRenderCommands();

            

            // should always have a camera if we've made it this far
            s.getCamera()->update();


            for (auto& rco : s.getRenderCommandsOrder().value())
            {
                RenderCommand& rc = s.getRenderCommand(rco);

                if (rc.getShaderIndex() != gpu.getActiveShaderIndex())
                {
                    gpu.useShader(rc.getShaderIndex());
                }

                if (rc.getMeshIndex() != gpu.getActiveMeshRenderableIndex())
                {
                    gpu.useMeshRenderable(rc.getMeshIndex());
                }

                if (rc.getTextureIndex() != gpu.getActiveTextureIndex())
                {
                    gpu.useTexture(rc.getTextureIndex());
                }

                //std::cout << "S:" << gpu.getActiveShaderIndex() << " M:" << gpu.getActiveMeshRenderableIndex() << " T:" << gpu.getActiveTextureIndex() << "\n";

                // gpu state has been set, now draw all actors which use this gpu state
                for (auto& ai : rc.getActorIndexes())
                {
                    Actor& a = s.getActor(ai);

                    //std::cout << "AS:" << a.getShaderIndex().value() << " AM:" << App::get().getScene()->getMesh(a.getMeshIndex().value()).getMeshRenderableIndex().value() << " AT:" << a.getTextureIndex().value() << "\n";

                    if (!a.isDeleted())
                    {
                        gpu.setShaderMat4("mvp",
                            s.getCamera()->getProjectionMatrix() *
                            s.getCamera()->getViewMatrix() *
                            a.getTransform().getMatrix());

                        gpu.drawMeshRenderable();
                    }
                }

            }

            
            
        }


        //std::cin.get();
    }

}