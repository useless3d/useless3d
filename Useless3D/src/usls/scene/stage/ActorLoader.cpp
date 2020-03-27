#include <iostream>

#include "usls/App.h"
#include "usls/scene/stage/ActorLoader.h"
#include "usls/scene/stage/transform/Rotation.h"
#include "usls/scene/mesh/MeshVertex.h"

namespace usls
{
    /*
        Possibly abusing the App singleton in this class's implementation. Just making
        note of that for a possible future refactor. The way this class is used in the
        Stage class to load actors, (created on stack, used, then destroyed) I'm not
        overly worried about it though.
    */

    ActorLoader::ActorLoader(Stage* stage, std::string actorFile) :
        headless(App::get().config.HEADLESS),
        currentStage(stage),
        currentActorFile(actorFile),
        currentAssetDirectory(actorFile.substr(0, actorFile.find_last_of('/'))) 
    {}

    void ActorLoader::execute()
    {
        Assimp::Importer importer;
        const aiScene* aiScene;
        this->getAssimpScene(this->currentActorFile, importer, aiScene);

        this->processNode(aiScene->mRootNode, aiScene);
    }

    void ActorLoader::getAssimpScene(std::string filePath, Assimp::Importer &importer, const aiScene* &scene) const
    {
        scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::string errorMessage = importer.GetErrorString();
            std::cout << "ERROR::ASSIMP::" << errorMessage << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }
    }

    void ActorLoader::processNode(aiNode* node, const aiScene* scene)
    {
        // For debugging
        //std::cout << "node:";
        //std::cout << node->mName.C_Str();
        //std::cout << " parent:";
        //if (node->mParent != NULL) {
        //    std::cout << node->mParent->mName.C_Str();
        //    std::cout << "\n";
        //}
        //else {
        //    std::cout << "ROOT\n";
        //}

        // If node has more than one mesh, log an error and exit (as I cannot think of a reason
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

        std::string actorName = this->generateUniqueActorName(node->mName.C_Str());

        this->processTransformable(node);

        this->currentMeshIndex = -1;
        this->currentMeshTextureIndex = -1;

        if (node->mNumMeshes == 1)
        {
            this->processMesh(node, scene);

            if (this->headless)
            {
                this->currentStage->addActor(Actor(actorName, this->currentTransform, this->currentMeshIndex));
            }
            else
            {
                int shaderIndex = this->findShaderId.value()(actorName);

                if (this->currentMeshTextureIndex != -1)
                {
                    this->currentStage->addActor(Actor(actorName, this->currentTransform, 
                        this->currentMeshIndex, shaderIndex, this->currentMeshTextureIndex));
                }
                else
                {
                    this->currentStage->addActor(Actor(actorName, this->currentTransform,
                        this->currentMeshIndex, shaderIndex));
                }
            }
        }
        else
        {
            // no mesh so this is an empty
            this->currentStage->addActor(Actor(actorName, this->currentTransform));
        }

        // Do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            this->processNode(node->mChildren[i], scene);
        }
    }

    void ActorLoader::processTransformable(aiNode* node)
    {
        aiVector3D aiScale;
        aiVector3D aiPosition;
        aiVector3D aiRotationAxis;
        float rotationAngle;
        node->mTransformation.Decompose(aiScale, aiRotationAxis, rotationAngle, aiPosition);

        glm::vec3 scale = glm::vec3(aiScale.x, aiScale.y, aiScale.z);
        glm::vec3 translation = glm::vec3(aiPosition.x, aiPosition.y, aiPosition.z);
        glm::vec3 rotationAxis = glm::vec3(aiRotationAxis.x, aiRotationAxis.y, aiRotationAxis.z);

        Rotation rotation;
        rotation.angle = rotationAngle * (180 / 3.124); // convert radian to degree
        rotation.axis = rotationAxis;

        this->currentTransform = Transform(translation, rotation, scale);
    }

    void ActorLoader::processMesh(aiNode* node, const aiScene* scene)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[0]];
        //std::cout << mesh->mName.C_Str();
        //std::cout << "\n";

        // process mesh
        std::vector<MeshVertex> vertices;
        std::vector<unsigned int> indices;

        // Walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            MeshVertex vertex;
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
        if (this->currentMeshIndex == -1)
        {
            // Did not locate an existing mesh, so create one
            this->currentMeshIndex = App::get().getScene()->addMesh(Mesh(mesh->mName.C_Str(), vertices, indices));
        }


        if (!this->headless)
        {
            // process materials
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            aiString str;
            material->GetTexture(aiTextureType_DIFFUSE, 0, &str);

            // if mesh does not contain a texture, exit
            if (str.length == 0)
            {
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
            if (this->currentMeshTextureIndex == -1)
            {
                this->currentMeshTextureIndex = App::get().getGPU()->loadTexture("diffuse", (this->currentAssetDirectory + "/" + str.C_Str()));
            }
        }
    }

    // verify actor name is unique, and if it is not, write to log to notify user that this is happening
    // so that they can address the situation if need be
    std::string ActorLoader::generateUniqueActorName(std::string name)
    {
        if (!this->currentStage->hasActorWithName(name))
        {
            return name;
        }

        std::string message = "While attempting to load object: " + name + " from file: " + this->currentActorFile
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