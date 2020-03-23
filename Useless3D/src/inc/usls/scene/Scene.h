#pragma once

#include <memory>
#include <vector>
#include <string>

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/mesh/MeshTexture.h"
#include "usls/scene/stage/Stage.h"
#include "usls/scene/Shader.h"


namespace usls 
{

    class Scene
    {
    private:
        bool                        headless;
        std::vector<Shader>         shaders;
        std::vector<Stage>          stages;
        std::vector<Mesh>           meshes;
        std::vector<MeshTexture>    textures;

        

    protected:
        void                        addShader(std::string vertName, std::string fragName);
        int                         addStage();
        Stage&                      getStage(int id);
        

    public:
                                    Scene();

        const std::vector<Mesh>&    getMeshes() const;
        unsigned int                addMesh(Mesh m);
        Mesh&                       getMesh(unsigned int index);

        const std::vector<MeshTexture>& getTextures() const;
        unsigned int                addTexture(MeshTexture t);
        MeshTexture&                getTexture(unsigned int index);

        bool                        loaded = false;
        void                        draw();

        virtual void                load() = 0;
        virtual void                loop() = 0;
        virtual void                end() = 0;

    };

}