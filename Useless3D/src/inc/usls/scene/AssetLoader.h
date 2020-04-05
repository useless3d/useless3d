#pragma once

#include <vector>
#include <string>
#include <functional>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/stage/Stage.h"
#include "usls/scene/transform/Transform.h"
#include "usls/scene/Shader.h"

using namespace usls::scene::stage;
using namespace usls::scene::transform;

namespace usls::scene 
{

	class AssetLoader
	{
	private:
		Assimp::Importer    aiImporter;
		const aiScene*      aiScene;

		bool                headless;
		Stage*              currentStage;
		std::string         currentActorFile;
		std::string         currentAssetDirectory;
		Transform           currentTransform;
		int                 currentMeshIndex;
		int                 currentMeshTextureIndex;

		void                processNode(aiNode* node);
		void                processTransformable(aiNode* node);
		void                processMesh(aiNode* node);
		std::string         generateUniqueActorName(std::string name);

	public:
		AssetLoader(Stage* stage, std::string actorFile);
		std::optional<std::function<int(std::string actorName)>> findShaderId;
		void                execute();


	};
	

}