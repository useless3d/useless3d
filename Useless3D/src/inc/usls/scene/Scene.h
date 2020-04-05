#pragma once

#include <memory>
#include <vector>
#include <string>

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/stage/Stage.h"


using namespace usls::scene::stage;
using namespace usls::scene::mesh;

namespace usls::scene 
{
	class Scene
	{
	private:
		const bool							headless;
		std::vector<Stage>					stages;
		std::vector<Mesh>					meshes;


	protected:
		int									addShader(std::string name, std::string vertName, std::string fragName);
		Stage&								addStage();
		Stage&								getStage(int index);


	public:
		Scene();
		~Scene();

		bool								loaded;
		const std::vector<Mesh>&			getMeshes() const;
		unsigned int						addMesh(Mesh m);
		Mesh&								getMesh(unsigned int index);


		void								draw();

		virtual void						load() = 0;
		virtual void						loop() = 0;

	};

}