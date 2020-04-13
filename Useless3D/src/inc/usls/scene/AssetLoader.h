#pragma once

#include <vector>
#include <string>
#include <functional>
#include <optional>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/stage/Stage.h"

#include "usls/scene/Shader.h"
#include "usls/scene/stage/Transform.h"
#include "usls/scene/armature/Armature.h"

using namespace usls::scene::stage;


namespace usls::scene 
{

	class AssetLoader
	{
	private:
		Assimp::Importer		aiImporter;
		const aiScene*			aiScene;

		bool					headless;
		Stage*					currentStage;
		std::string				currentAssetFile;
		std::string				currentAssetDirectory;
		Transform				currentTransform;
		std::optional<size_t>   currentMeshIndex;
		std::optional<size_t>   currentMeshTextureIndex;
		std::optional<armature::Armature> currentArmature;


		void					processAnimations();
		void					processArmatureNode(aiNode* node);
		void					processActorNode(aiNode* node);
		void					processTransformable(aiNode* node);
		void					processMesh(aiNode* node);
		std::string				generateUniqueActorName(std::string name);

	public:
								AssetLoader(Stage* stage, std::string assetFile);

		std::optional<std::function<int(std::string actorName)>>	findShaderId;

		void					loadActors();
		size_t					loadArmature();


	};
	

}