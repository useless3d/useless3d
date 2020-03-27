#pragma once

#include <vector>
#include <string>

#include "usls/scene/Shader.h"
#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/mesh/MeshTexture.h"


namespace usls
{
    class GPU
    {
    private:
        std::string                 shaderDirectory;
        std::vector<Shader>         shaders;
        std::vector<MeshTexture>    textures;
        std::vector<MeshRenderable> meshRenderables;

        int         activeShaderIndex;
        int         activeMeshRenderableIndex;
        int         activeTextureIndex;

    public:
                    GPU(std::string shaderDirectory);

        void        enableDepthTest();
        void        clearBuffers(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);
        void        drawLinesOnly();

        const int   getActiveShaderIndex() const;
        const int   getActiveMeshRenderableIndex() const;
        const int   getActiveTextureIndex() const;

        int         loadShader(const std::string name, const std::string vertFile, const std::string fragFile);
        int         loadMesh(Mesh& m);
        int         loadTexture(std::string type, std::string path);

        void        useTexture(int textureIndex);
        const std::vector<MeshTexture>& getTextures() const;
        void        clearTexture();
        
        void        useShader(int shaderIndex);
        void        setShaderBool(const std::string &name, bool value) const;
        void        setShaderInt(const std::string &name, int value) const;
        void        setShaderFloat(const std::string &name, float value) const;
        void        setShaderMat4(const std::string &name, glm::mat4 value) const;

        void        useMeshRenderable(int meshRenderableIndex);
        void        drawMeshRenderable();

        void        wipe();

        


    };
}