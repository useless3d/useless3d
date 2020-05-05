#include <iostream>

#define GLM_FORCE_ALIGNED_GENTYPES
#include <glm/gtx/string_cast.hpp>

#include "usls/App.h"
#include "usls/scene/Scene.h"
#include "usls/scene/mesh/Vertex.h"
#include "usls/scene/mesh/Texture.h"


namespace usls::scene
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

	size_t Scene::addAnimation(Animation a)
	{
		this->animations.push_back(a);
		return this->animations.size() - 1;
	}

	size_t Scene::addShader(std::string name, std::string vertName, std::string fragName)
	{
		return App::get().getGPU()->loadShader(name, vertName, fragName);
	}

	Stage& Scene::addStage()
	{
		this->stages.push_back(Stage(this->headless));
		return this->getStage(this->stages.size() - 1);
	}

	Stage& Scene::getStage(size_t index)
	{
		return this->stages.at(index);
	}

	const std::vector<Mesh>& Scene::getMeshes() const
	{
		return this->meshes;
	}

	const std::vector<Animation>& Scene::getAnimations() const
	{
		return this->animations;
	}

	size_t Scene::addMesh(Mesh m)
	{
		if (!this->headless)
		{
			m.setMeshRenderableIndex(App::get().getGPU()->loadMesh(m));
		}
		this->meshes.push_back(m);
		return this->meshes.size() - 1;
	}

	Mesh& Scene::getMesh(size_t index)
	{
		return this->meshes.at(index);
	}

	Animation& Scene::getAnimation(size_t index)
	{
		return this->animations.at(index);
	}

	void Scene::updateAnimations(double runTime)
	{
		for (auto& s : this->stages)
		{
			s.updateActorAnimations(runTime);
		}
	}

	void Scene::savePreviousTransforms()
	{
		for (auto& s : this->stages)
		{
			s.savePreviousTransforms();
		}
	}

	void Scene::loop(double deltaTime)
	{
		for (auto& s : this->stages)
		{
			s.executeControllers(deltaTime);
		}
	}

    void Scene::draw(double alpha)
    {
        GPU& gpu = App::get().getGPU().value();

        for (auto& s : this->stages)
        {
			if (!s.isVisible())
			{
				continue;
			}

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

                // gpu state has been set, now draw all actors which use this gpu state
                for (auto& ai : rc.getActorIndexes())
                {
                    Actor* a = s.getActor(ai);

                    if (!a->isDeleted() && a->isVisible())
                    {
						// If this actor is animated, send the bone transforms of it's armature to the shader
						if (a->isAnimated())
						{
							gpu.setShaderMat4("mvp", s.getCamera()->getProjectionMatrix() * s.getCamera()->getViewMatrix());

							auto& mesh = a->getMesh();
							auto& armature = a->getArmature();
							
							size_t boneIndex = 0;
							for (auto& activeBone : a->getActiveBones().value())
							{
								glm::mat4 meshBoneTransform = mesh.getGlobalInverseMatrix() * armature.getBone(activeBone.first).matrix * mesh.getBone(boneIndex).offsetMatrix;

								gpu.setShaderMat4(activeBone.second, meshBoneTransform);

								boneIndex++;
							}

						}
						else
						{
							//gpu.setShaderMat4("mvp", s.getCamera()->getProjectionMatrix() * s.getCamera()->getViewMatrix() * a->getWorldMatrix());
							gpu.setShaderMat4("mvp", s.getCamera()->getProjectionMatrix() * s.getCamera()->getViewMatrix() * a->getWorldRenderMatrix(alpha));
						}

                        gpu.drawMeshRenderable();
                    }
                }

            }

            
            
        }


    }

}