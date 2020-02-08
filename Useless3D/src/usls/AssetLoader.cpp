#include "inc/AssetLoader.h"
#include "inc/Logger.h"

#include <iostream>

namespace usls
{
    std::string AssetLoader::currentAssetDirectory = "";


    void AssetLoader::loadStage(std::string file, Stage* stage)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            if (Logger::isEnabled()) {
                std::string errorMessage = importer.GetErrorString();
                Logger::log("ERROR::ASSIMP::" + errorMessage);
            }
            exit(EXIT_FAILURE);
        }

        currentAssetDirectory = pathWithoutFilename(file);
        
        processNode(scene->mRootNode, scene, [&](aiNode* node, Mesh* mesh) {

            if (mesh != nullptr) {
                std::cout << mesh->getName() << "\n";
            }

            //std::cout << stage->getNumProps() + "\n";

        });
        

        //processNode(scene->mRootNode, scene);

    }

    std::string AssetLoader::pathWithoutFilename(std::string filePath)
    {
        return filePath.substr(0, filePath.find_last_of('/'));
    }

    void AssetLoader::processNode(aiNode* node, const aiScene* scene, std::function<void(aiNode* node, Mesh* mesh)> cb)
    //void AssetLoader::processNode(aiNode* node, const aiScene* scene)
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


        Mesh* ourMesh = nullptr;

        if (node->mNumMeshes == 1) // process mesh
        {
            processMesh(ourMesh, node, scene);
        }

        // asset specific logic, the prop/actor would be built within this function callback
        cb(node, ourMesh);


        // Do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene, cb);
        }

    }

    void AssetLoader::processMesh(Mesh* ourMesh, aiNode* node, const aiScene* scene)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[0]];
        std::cout << mesh->mName.C_Str();
        std::cout << "\n";

        // process mesh
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        // Walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

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
            else {
                vertex.textureCoordinates = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);

        }

        // now walk through each of the mesh's faces (a face is a mesh's triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {

            aiFace face = mesh->mFaces[i];

            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
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
        std::cout << texture.path << "\n";

        ourMesh = Mesh::createMesh(mesh->mName.C_Str(), vertices, indices, texture);

    }

}