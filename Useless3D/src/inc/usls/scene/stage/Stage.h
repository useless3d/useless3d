#pragma once

#include <vector>
#include <string>
#include <optional>
#include <memory>
#include <functional>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "usls/scene/stage/mesh/Mesh.h"
#include "usls/scene/stage/camera/Camera.h"
#include "usls/scene/Shader.h"
#include "usls/scene/stage/Prop.h"

namespace usls
{
    class Stage
    {
    private:
        bool                            headless;
        std::optional<Shader>           shader; // optional shader to use instead of the default app shader
        std::string                     name;
        std::vector<std::unique_ptr<Prop>> props;
        std::optional<std::unique_ptr<Camera>> camera;
        std::vector<std::unique_ptr<Mesh>> meshes;
        std::string                     currentAssetDirectory = "";

        void                            getAssimpScene(std::string filePath, Assimp::Importer &importer, const aiScene* &scene) const;
        void                            processNode(aiNode* node, const aiScene* scene, std::function<void(aiNode* node, Mesh* mesh)> cb);
        Mesh*                           processMesh(aiNode* node, const aiScene* scene);

    public:
        Stage(Stage&&) = default;
        Stage(std::string name);
        Stage(std::string name, std::unique_ptr<Camera> camera);
        ~Stage();
        void                addProp(std::string filePath);
        void                setShader(Shader shader);
        void                draw(Shader* appShader);

        const int           getMeshCount() const;
        const int           getPropCount() const;
  

    };
}