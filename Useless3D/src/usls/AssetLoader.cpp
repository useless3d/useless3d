#include "inc/AssetLoader.h"
#include "inc/Logger.h"
#include "inc/Prop.h"

#include <iostream>

namespace usls
{
    std::string AssetLoader::currentAssetDirectory = "";


    void AssetLoader::loadStage(std::string file, Stage* stage)
    {
        currentAssetDirectory = pathWithoutFilename(file);

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            if (Logger::isEnabled()) 
            {
                std::string errorMessage = importer.GetErrorString();
                Logger::log("ERROR::ASSIMP::" + errorMessage);
            }
            exit(EXIT_FAILURE);
        }

        processNode(scene->mRootNode, scene, [&](aiNode* node, Mesh* const mesh) {

            if (mesh != nullptr) 
            {
                //std::cout << mesh->getName() << "\n";

                aiVector3D aiScale;
                aiVector3D aiPosition;
                aiVector3D aiRotationAxis;
                float rotationAngle;
                node->mTransformation.Decompose(aiScale, aiRotationAxis, rotationAngle, aiPosition);

                glm::vec3 scale = glm::vec3(aiScale.x, aiScale.y, aiScale.z);
                glm::vec3 translation = glm::vec3(aiPosition.x, aiPosition.y, aiPosition.z);
                glm::vec3 rotationAxis = glm::vec3(aiRotationAxis.x, aiRotationAxis.y, aiRotationAxis.z);

                Rotation rotation;
                rotation.angle = rotationAngle;
                rotation.axis = rotationAxis;

                stage->addProp(Prop(mesh, translation, rotation, scale));

            }

        });

    }

    std::string AssetLoader::pathWithoutFilename(std::string filePath)
    {
        return filePath.substr(0, filePath.find_last_of('/'));
    }

    void AssetLoader::processNode(aiNode* node, const aiScene* scene, std::function<void(aiNode* node, Mesh* mesh)> cb)
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
            if (Logger::isEnabled())
            {
                std::string nodeName = node->mName.C_Str();
                Logger::log("AssetLoader ERROR: The following node contains more than one mesh: " + nodeName);
            }
            exit(EXIT_FAILURE);
        }


        if (node->mNumMeshes == 1) // process mesh
        {
            Mesh* const ourMesh = processMesh(node, scene);
            cb(node, ourMesh);
        }
        else
        {
            cb(node, nullptr);
        }

        // Do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene, cb);
        }

    }

    Mesh* const AssetLoader::processMesh(aiNode* node, const aiScene* scene)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[0]];
        //std::cout << mesh->mName.C_Str();
        //std::cout << "\n";

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

        // process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &str);

        Texture texture;
        texture.type = "diffuse";
        texture.path = currentAssetDirectory + "/";
        texture.path += str.C_Str();

        return Mesh::createMesh(mesh->mName.C_Str(), vertices, indices, texture);

    }

}