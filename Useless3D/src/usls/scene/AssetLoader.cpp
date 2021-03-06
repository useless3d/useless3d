#include <iostream>

#include <glm/gtx/string_cast.hpp>
#include "glm/gtc/quaternion.hpp"

#include "usls/App.h"
#include "usls/scene/AssetLoader.h"
#include "usls/scene/mesh/Vertex.h"
#include "usls/helpers.h"


namespace usls::scene
{
	AssetLoader::AssetLoader(Stage* stage, std::string assetFile, bool dynamic) :
        headless(App::get().config.HEADLESS),
        currentStage(stage),
        currentAssetFile(assetFile),
        currentAssetDirectory(assetFile.substr(0, assetFile.find_last_of('/'))),
		currentIsDynamic(dynamic)
    {
        this->aiScene = this->aiImporter.ReadFile(this->currentAssetFile, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

        if (!this->aiScene || !this->aiScene->mRootNode)
        {
            std::string errorMessage = this->aiImporter.GetErrorString();
            std::cout << "ERROR::ASSIMP::" << errorMessage << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }
    }

    void AssetLoader::loadActors()
    {
        this->processActorNode(this->aiScene->mRootNode);
    }

	std::optional<size_t> AssetLoader::getExistingAnimationIndex(std::string animationName)
	{
		size_t i = 0;
		for (auto& a : App::get().getScene()->getAnimations())
		{
			if (a.name == animationName)
			{
				return i;
			}
			i++;
		}
		return std::nullopt;
	}

	void AssetLoader::processAnimations()
	{
		for (unsigned int i = 0; i < this->aiScene->mNumAnimations; i++)
		{
			std::string animationName = this->aiScene->mAnimations[i]->mName.C_Str();

			// if an animation exists with the same name, use that animation
			auto existingAnimationIndex = this->getExistingAnimationIndex(animationName);
			
			if (existingAnimationIndex)
			{
				// obtain this animation name relative to the armature
				auto name = explode_string(animationName, '|')[1];

				this->currentArmature->addAnimation(name, existingAnimationIndex.value());
			}
			// otherwise create a new animation
			else
			{

				// create a new animation
				auto a = Animation();
				a.name = this->aiScene->mAnimations[i]->mName.C_Str();
				a.duration = this->aiScene->mAnimations[i]->mDuration;
				a.tps = this->aiScene->mAnimations[i]->mTicksPerSecond;

				// add all channels to animation

				for (unsigned int j = 0; j < this->aiScene->mAnimations[i]->mNumChannels; j++)
				{
					auto c = Channel();

					// positions
					for (unsigned int k = 0; k < this->aiScene->mAnimations[i]->mChannels[j]->mNumPositionKeys; k++)
					{
						auto position = this->aiScene->mAnimations[i]->mChannels[j]->mPositionKeys[k].mValue;
						auto time = (float)this->aiScene->mAnimations[i]->mChannels[j]->mPositionKeys[k].mTime;
						c.positionKeyTimes.push_back(time);
						c.positionKeyValues.push_back(glm::vec3(position.x, position.y, position.z));
					}

					// rotations
					for (unsigned int k = 0; k < this->aiScene->mAnimations[i]->mChannels[j]->mNumRotationKeys; k++)
					{
						auto rotation = this->aiScene->mAnimations[i]->mChannels[j]->mRotationKeys[k].mValue;
						auto time = (float)this->aiScene->mAnimations[i]->mChannels[j]->mPositionKeys[k].mTime;
						c.rotationKeyTimes.push_back(time);
						c.rotationKeyValues.push_back(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));
					}

					// scalings
					for (unsigned int k = 0; k < this->aiScene->mAnimations[i]->mChannels[j]->mNumScalingKeys; k++)
					{
						auto scale = this->aiScene->mAnimations[i]->mChannels[j]->mScalingKeys[k].mValue;
						auto time = (float)this->aiScene->mAnimations[i]->mChannels[j]->mPositionKeys[k].mTime;
						c.scalingKeyTimes.push_back(time);
						c.scalingKeyValues.push_back(glm::vec3(scale.x, scale.y, scale.z));
					}

					// add channel to animation
					a.channels[this->aiScene->mAnimations[i]->mChannels[j]->mNodeName.C_Str()] = c;
				}

				// add animation to scene's animations container, retrieving index
				auto ai = App::get().getScene()->addAnimation(a);

				// obtain this animation name relative to the armature
				auto name = explode_string(a.name, '|')[1];

				// add this animation name/index to the armature's animations vector
				this->currentArmature->addAnimation(name, ai);
			}
		}
	}

	void AssetLoader::processArmatureNode(aiNode* node)
	{
		std::string nodeName = node->mName.C_Str();

		if (nodeName != "RootNode" && !string_contains("_end", nodeName))
		{
			std::string boneName = nodeName;
			std::string nodeParentName = node->mParent->mName.C_Str();

			if (nodeParentName == "RootNode")
			{
				this->currentArmature = usls::scene::armature::Armature(boneName);
			}

			usls::scene::armature::Bone bone;
			bone.name = boneName;
			bone.parentName = nodeParentName == "RootNode" ? boneName : node->mParent->mName.C_Str();

			this->currentArmature->addBone(bone);
		}

		this->processedNodes.push_back(nodeName);

		// Do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			this->processArmatureNode(node->mChildren[i]);
		}
	}

	bool AssetLoader::isRootArmatureNode(aiNode* node)
	{
		// if this node has children, and no mesh, assume that it is an armature
		// (this is very naive, but should work for the time being so we can move forward
		// with skeletal animation implementation. This method can be revised in the future
		// to be more accurate)
		std::string nodeName = node->mParent->mName.C_Str();
		if (nodeName == "RootNode" && node->mNumChildren > 0 && node->mNumMeshes == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

    void AssetLoader::processActorNode(aiNode* node)
    {
        // If node has more than one mesh, display an error and exit (as I cannot think of a reason
        // why a node would have more than one mesh at this time, therefore if we ever receive
        // an error here we can re-examine our thought process)
        // Well this answers my question: https://github.com/assimp/assimp/issues/314 however I'm
        // not implementing support for multiple meshes per node until need be
        if (node->mNumMeshes > 1)
        {
            std::string nodeName = node->mName.C_Str();
            std::cout << "AssetLoader ERROR: The following node contains more than one mesh: " << nodeName << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }

        
		std::string nodeName = node->mName.C_Str();

		if (nodeName == "RootNode")
		{
			this->currentGlobalInverseMatrix = glm::inverse(this->aiMatrix4x4ToGlm(node->mTransformation));
		}

        if (nodeName != "RootNode" && !sin_vector(nodeName, this->processedNodes))
        {
			
			if (this->isRootArmatureNode(node))
			{
				this->processArmatureNode(node);
				this->processAnimations();

				// Obtain parent indexes for each bone using their
				// boneNames (done so that these indexes can be used at runtime instead
				// of loops and string comparisons)
				for (auto& b : this->currentArmature->getBones()) // ignore intellisense error for getBones()
				{
					// get index of parent
					b.parent = this->currentArmature->getBoneIndex(b.parentName);
				}

			}
			else
			{
				std::string actorName = this->generateUniqueActorName(node->mName.C_Str());

				this->processTransformable(node);

				this->currentMeshIndex.reset();
				this->currentMeshTextureIndex.reset();

				auto actor = Actor(actorName, this->currentTransform);
				actor.setDynamic(this->currentIsDynamic);

				if (node->mNumMeshes == 1)
				{
					this->processMesh(node);

					actor.setMeshIndex(this->currentMeshIndex.value());
					if (this->currentArmature)
					{
						actor.setArmature(this->currentArmature.value());

						// set activeBones mapping
						std::vector<std::pair<size_t, std::string>> activeBones;
						size_t index = 0;
						for (auto& meshBone : App::get().getScene()->getMesh(this->currentMeshIndex.value()).getBones())
						{
							activeBones.push_back(std::pair<size_t, std::string>(actor.getArmature().getBoneIndex(meshBone.name), "bones[" + std::to_string(index) + "]"));
							index++;
						}

						actor.setActiveBones(activeBones);

					}

					if (!this->headless)
					{
						actor.setTextureIndex(this->currentMeshTextureIndex.value());

						// if findShaderId lambda is not defined, then use one of the default shaders
						// as this means the user did not explicitly pass a shader index to be used
						if (!findShaderId)
						{
							if (!this->currentArmature)
							{
								actor.setShaderIndex(0); // actor does not have an armature so use default (non-skinned) shader
							}
							else
							{
								actor.setShaderIndex(1); // actor has an armature so it's a skinned mesh, use default skinned shader
							}
						}
						else
						{
							actor.setShaderIndex(this->findShaderId.value()(actorName));
						}						
					}
				}

				this->currentStage->addActor(actor);
			}

			
        }

        // Do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            this->processActorNode(node->mChildren[i]);
        }
    }

    void AssetLoader::processTransformable(aiNode* node)
    {
        aiVector3D aiScale;
        aiVector3D aiPosition;
		aiQuaternion aiRotation;
        node->mTransformation.Decompose(aiScale, aiRotation, aiPosition);

        glm::vec3 scale = glm::vec3(aiScale.x, aiScale.y, aiScale.z);
        glm::vec3 translation = glm::vec3(aiPosition.x, aiPosition.y, aiPosition.z);
		glm::quat rotation = glm::quat(aiRotation.w, aiRotation.x, aiRotation.y, aiRotation.z);		

        this->currentTransform = Transform(translation, rotation, scale);
    }

    void AssetLoader::processMesh(aiNode* node)
    {
        aiMesh* aiMesh = this->aiScene->mMeshes[node->mMeshes[0]];
		auto mesh = Mesh(aiMesh->mName.C_Str());

        // walk through each of the mesh's vertices
		std::vector<Vertex> vertices;
		for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;

            // position
            vector.x = aiMesh->mVertices[i].x;
            vector.y = aiMesh->mVertices[i].y;
            vector.z = aiMesh->mVertices[i].z;
            vertex.position = vector;

            // normal
            vector.x = aiMesh->mNormals[i].x;
            vector.y = aiMesh->mNormals[i].y;
            vector.z = aiMesh->mNormals[i].z;
            vertex.normal = vector;

            // texture coordinates
            if (aiMesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = aiMesh->mTextureCoords[0][i].x;
                vec.y = aiMesh->mTextureCoords[0][i].y;
                vertex.textureCoordinates = vec;
            }
            else
            {
                vertex.textureCoordinates = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }

		mesh.setVertices(vertices);


        // now walk through each of the mesh's faces (a face is a mesh's triangle) and retrieve the corresponding vertex indices.
		std::vector<unsigned int> indices;
        for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
        {
            aiFace face = aiMesh->mFaces[i];

            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

		mesh.setIndices(indices);


		// if mesh has bones, process bones
		std::vector<mesh::Bone> bones;

		if (aiMesh->HasBones())
		{
			for (unsigned int i = 0; i < aiMesh->mNumBones; i++)
			{
				auto b = mesh::Bone();
				b.name = aiMesh->mBones[i]->mName.C_Str();
				b.offsetMatrix = this->aiMatrix4x4ToGlm(aiMesh->mBones[i]->mOffsetMatrix);
				bones.push_back(b);

				for (unsigned int j = 0; j < aiMesh->mBones[i]->mNumWeights; j++)
				{
					mesh.addVertexWeight(aiMesh->mBones[i]->mWeights[j].mVertexId, i, aiMesh->mBones[i]->mWeights[j].mWeight);
				}				
			}
		}

		mesh.setBones(bones);


        // Does the exact same mesh exist? If so use the index of that mesh.

        // Loop through each existing mesh and determine if the verticies are the same.
        // (Probably a better way to do this...hashes maybe?)
        int meshIndex = 0;
        for (auto& m : App::get().getScene()->getMeshes())
        {
            // If mesh exists, use the index of the existing mesh...
            if (vertices == m.getVertices())
            {
                this->currentMeshIndex = meshIndex;
                break;
            }
            meshIndex++;
        }
        // ...otherwise, save it within scene->meshes and save the new index
        if (!this->currentMeshIndex)
        {
			mesh.setGlobalInverseMatrix(this->currentGlobalInverseMatrix);

            this->currentMeshIndex = App::get().getScene()->addMesh(mesh);
        }


        if (!this->headless)
        {
            // process materials
            aiMaterial* material = this->aiScene->mMaterials[aiMesh->mMaterialIndex];
            aiString str;
            material->GetTexture(aiTextureType_DIFFUSE, 0, &str);

            // if mesh does not contain a texture, use default texture
            if (str.length == 0)
            {
				this->currentMeshTextureIndex = 0;
                return;
            }

            // determine if the texture already exists, if it does use it's index...
            int meshTextureIndex = 0;
            for (auto& t : App::get().getGPU()->getTextures()) // ignore intellisense error for getTextures()
            {
                if (t.path == (this->currentAssetDirectory + "/" + str.C_Str()))
                {
                    this->currentMeshTextureIndex = meshTextureIndex;
                    break;
                }
                meshTextureIndex++;
            }
            // ...otherwise create a new texture
            if (!this->currentMeshTextureIndex)
            {
                this->currentMeshTextureIndex = App::get().getGPU()->loadTexture("diffuse", (this->currentAssetDirectory + "/" + str.C_Str()));
            }
        }
    }

    // verify actor name is unique, and if it is not, write to log to notify user that this is happening
    // so that they can address the situation if need be
    std::string AssetLoader::generateUniqueActorName(std::string name)
    {
        if (!this->currentStage->hasActorWithName(name))
        {
            return name;
        }

        std::string message = "While attempting to load object: " + name + " from file: " + this->currentAssetFile
            + " an existing actor contained this name. The following name has been used instead: ";

        int uniqueNumber = 0;
        std::string newName = (name + std::to_string(uniqueNumber));
        while (this->currentStage->hasActorWithName(newName))
        {
            uniqueNumber++;
            newName = (name + std::to_string(uniqueNumber));
        }

        App::get().logger.log(message + newName);

        return newName;
    }

	glm::mat4 AssetLoader::aiMatrix4x4ToGlm(const aiMatrix4x4 &from)
	{
		glm::mat4 to;
		//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
		to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
		to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
		to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
		to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
		return to;
	}

}