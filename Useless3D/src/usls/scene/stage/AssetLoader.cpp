#include <iostream>

#include "glm/gtc/quaternion.hpp"

#include "usls/App.h"
#include "usls/scene/AssetLoader.h"
#include "usls/scene/mesh/Vertex.h"
#include "usls/helpers.h"


namespace usls::scene
{
	AssetLoader::AssetLoader(Stage* stage, std::string assetFile) :
        headless(App::get().config.HEADLESS),
        currentStage(stage),
        currentAssetFile(assetFile),
        currentAssetDirectory(assetFile.substr(0, assetFile.find_last_of('/')))
    {
        this->aiScene = this->aiImporter.ReadFile(this->currentAssetFile, aiProcess_Triangulate | aiProcess_FlipUVs);

        //if (!this->aiScene || this->aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !this->aiScene->mRootNode)
        if (!this->aiScene || !this->aiScene->mRootNode)
        //if (this->aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
        {
            std::string errorMessage = this->aiImporter.GetErrorString();
            std::cout << "ERROR::ASSIMP::" << errorMessage << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }
    }

	void AssetLoader::loadArmature()
	{
		//std::cout << "> Nodes\n";

		this->processArmatureNode(this->aiScene->mRootNode);

		//std::cout << "\n---------\n";
		//for (auto& b : this->currentArmature->getBones())
		//{
		//	std::cout << "name: " << b.name << "\n";
		//	std::cout << "children: ";
		//	for (auto& c : b.children)
		//	{
		//		std::cout << c << ",";
		//	}
		//	std::cout << "\n";
		//}

		// Obtain parent and child indexes for each bone using their
		// boneNames (done so that these indexes can be used at runtime instead
		// of loops and string comparisons)
		for (auto& b : this->currentArmature->getBones())
		{
			std::cout << b.name << "-" << b.parentName << "\n";
			// get index of parent
			b.parent = this->currentArmature->getBoneIndex(b.parentName);

			// get indexes of all children
			for (auto& c : b.childNames)
			{
				b.children.push_back(this->currentArmature->getBoneIndex(c));
			}
		}


		std::cout << "\n---------\n";
		size_t i = 0;
		for (auto& b : this->currentArmature->getBones())
		{
			std::cout << "name: " << b.name << " " << i << "\n";
			std::cout << "parent:" << b.parent << "\n";
			std::cout << "children: ";
			for (auto& c : b.children)
			{
				std::cout << c << ",";
			}
			std::cout << "\n";
			i++;
		}


		//std::cout << "> Animations\n";
		//for (unsigned int i = 0; i < this->aiScene->mNumAnimations; i++)
		//{
		//	std::cout << "  > " << this->aiScene->mAnimations[i]->mName.C_Str() << " - TPS: " << this->aiScene->mAnimations[i]->mTicksPerSecond << " - DUR: " << this->aiScene->mAnimations[i]->mDuration << "\n";

		//	for (unsigned int j = 0; j < this->aiScene->mAnimations[i]->mNumChannels; j++)
		//	{
		//		std::cout << "      > " << this->aiScene->mAnimations[i]->mChannels[j]->mNodeName.C_Str() << "\n";

		//		for (unsigned int k = 0; k < this->aiScene->mAnimations[i]->mChannels[j]->mNumScalingKeys; k++)
		//		{
		//			const aiVector3D& scale = this->aiScene->mAnimations[i]->mChannels[j]->mScalingKeys[k].mValue;
		//			std::cout << "			> (" << scale.x << "," << scale.y << "," << scale.z << ")\n";

		//		}

		//	}
		//}


	}

    void AssetLoader::loadActors()
    {
        this->processActorNode(this->aiScene->mRootNode);
    }

	void AssetLoader::processArmatureNode(aiNode* node)
	{
		// For debugging
		std::cout << "  > " << node->mName.C_Str() << " - Parent: " << (node->mParent != NULL ? node->mParent->mName.C_Str() : "RootNode") << "\n";

		if (node->mNumMeshes != 0)
		{
			std::string nodeName = node->mName.C_Str();
			std::cout << "AssetLoader ERROR: attempting to load armature from file that also contains mesh data (this is not supported)\n";
			std::cin.get();
			exit(EXIT_FAILURE);
		}

		std::string nodeName = node->mName.C_Str();

		if (nodeName != "RootNode" && !string_contains("_end", nodeName))
		{
			std::string boneName = node->mName.C_Str();

			std::string nodeParentName = node->mParent->mName.C_Str();

			if (nodeParentName == "RootNode")
			{
				this->currentArmature = usls::scene::armature::Armature(boneName);
			}
			
			this->processTransformable(node);


			usls::scene::armature::Bone bone;
			bone.name = boneName;
			bone.parentName = nodeParentName == "RootNode" ? boneName : node->mParent->mName.C_Str();
			bone.currentTransform = this->currentTransform;

			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				std::string childName = node->mChildren[i]->mName.C_Str();
				if (!string_contains("_end", childName))
				{
					bone.childNames.push_back(childName);
				}
				
			}

			this->currentArmature->addBone(bone);
			
		}

		// Do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			this->processArmatureNode(node->mChildren[i]);
		}
	}

    void AssetLoader::processActorNode(aiNode* node)
    {
        // For debugging
        std::cout << "  > " << node->mName.C_Str() << " - Parent: " << (node->mParent != NULL ? node->mParent->mName.C_Str() : "RootNode") << "\n";
        
        //std::cout << " parent:";
        //if (node->mParent != NULL) {
        //    std::cout << node->mParent->mName.C_Str();
        //    std::cout << "\n";
        //}
        //else {
        //    std::cout << "ROOT\n";
        //}

        // If node has more than one mesh, display an error and exit (as I cannot think of a reason
        // why a node would have more than one mesh at this time, therefore if we ever receive
        // an error here we can re-examine our thought process)
        // Well this answers my question: https://github.com/assimp/assimp/issues/314 however i'm
        // not implementing support for multiple meshes per node until a reason is brought to light
        if (node->mNumMeshes > 1)
        {
            std::string nodeName = node->mName.C_Str();
            std::cout << "AssetLoader ERROR: The following node contains more than one mesh: " << nodeName << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }

        
		std::string nodeName = node->mName.C_Str();

        if (nodeName != "RootNode")
        {
			// is this an armature?


			std::string actorName = this->generateUniqueActorName(node->mName.C_Str());

            this->processTransformable(node);

			this->currentMeshIndex.reset();
            this->currentMeshTextureIndex.reset();

			

            auto actor = Actor(actorName, this->currentTransform);

            if (node->mNumMeshes == 1)
            {
                this->processMesh(node);

                actor.setMeshIndex(this->currentMeshIndex.value());

                if (!this->headless)
                {
                    actor.setShaderIndex(this->findShaderId.value()(actorName));
                    actor.setTextureIndex(this->currentMeshTextureIndex.value());
                }
            }

            this->currentStage->addActor(actor);
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

		//std::cout << "	> position:" << translation.x << "," << translation.y << "," << translation.z << "\n";
		//std::cout << "	> scale:" << scale.x << "," << scale.y << "," << scale.z << "\n";

        this->currentTransform = Transform(translation, rotation, scale);
    }

    void AssetLoader::processMesh(aiNode* node)
    {
        aiMesh* mesh = this->aiScene->mMeshes[node->mMeshes[0]];
        //std::cout << mesh->mName.C_Str();
        //std::cout << "\n";

        if (mesh->HasBones())
        {
            std::cout << "      > Bones\n";
            for (unsigned int i = 0; i < mesh->mNumBones; i++)
            {
                std::cout << "          > " << mesh->mBones[i]->mName.C_Str() << "\n";
            }
        }

        // process mesh
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        // Walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;

            // position
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.position = vector;

            // normal
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;

            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.textureCoordinates = vec;
            }
            else
            {
                vertex.textureCoordinates = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);

        }

        // now walk through each of the mesh's faces (a face is a mesh's triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        // Does the exact same mesh exist? If so use the index of that mesh.

        // Loop through each existing mesh and determine if the verticies are the same.
        // (I can't imagine this will scale well, and a more clever solution should be implemented)
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
        // ...otherwise create a new mesh, save it within meshes and save the new index
        if (!this->currentMeshIndex)
        {
            this->currentMeshIndex = App::get().getScene()->addMesh(Mesh(mesh->mName.C_Str(), vertices, indices));
        }


        if (!this->headless)
        {
            // process materials
            aiMaterial* material = this->aiScene->mMaterials[mesh->mMaterialIndex];
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
            for (auto& t : App::get().getGPU()->getTextures()) // ignore intellisense error for getTextures(), not sure why it doesn't understand it's legit
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

}