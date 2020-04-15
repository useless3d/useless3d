#pragma once

#include <memory>
#include <vector>
#include <string>

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/stage/Stage.h"
#include "usls/scene/armature/Armature.h"
#include "usls/scene/animation/Animation.h"


using namespace usls::scene::stage;
using namespace usls::scene::mesh;
using namespace usls::scene::armature;
using namespace usls::scene::animation;


namespace usls::scene 
{
	class Scene
	{
	private:
		const bool							headless;
		std::vector<Stage>					stages;
		std::vector<Mesh>					meshes;
		std::vector<Armature>				armatures;
		std::vector<Animation>				animations;


	protected:
		size_t								addShader(std::string name, std::string vertName, std::string fragName);
		Stage&								addStage();
		Stage&								getStage(size_t index);


	public:
		Scene();
		~Scene();

		bool								loaded;
		const std::vector<Mesh>&			getMeshes() const;
		size_t								addMesh(Mesh m);
		Mesh&								getMesh(size_t index);

		size_t								addAnimation(Animation a);
		size_t								addArmature(Armature a);

		Armature&							getArmature(size_t index);
		std::vector<Armature>&				getArmatures();
		const std::vector<Animation>&		getAnimations() const;
		Animation&							getAnimation(size_t index);

		void								updateAnimations(double runTime);
		void								draw();

		virtual void						load() = 0;
		virtual void						loop() = 0;

	};

}