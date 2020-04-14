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
#include "usls/scene/mesh/VertexBoneData.h"

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
		std::optional<size_t>	currentArmatureIndex;
		std::vector<std::string> processedNodes;
		std::vector<mesh::VertexBoneData> currentMeshBones;


		void					processAnimations();
		void					processArmatureNode(aiNode* node);
		void					processActorNode(aiNode* node);
		void					processTransformable(aiNode* node);
		void					processMesh(aiNode* node);
		bool					isRootArmatureNode(aiNode* node);
		
		std::string				generateUniqueActorName(std::string name);
		glm::mat4				aiMatrix4x4ToGlm(const aiMatrix4x4 &from);

	public:
								AssetLoader(Stage* stage, std::string assetFile);

		std::optional<std::function<int(std::string actorName)>>	findShaderId;

		void					loadActors();



	};
	

}