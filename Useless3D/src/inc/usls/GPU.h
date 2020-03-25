#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/mesh/MeshTexture.h"


namespace usls
{
    class GPU
    {
    private:
        std::string shaderDirectory;

    public:
                    GPU(std::string shaderDirectory);
        int         loadShader(const std::string vertFile, const std::string fragFile);
        void        loadMesh(Mesh& m);
        void        loadTexture(MeshTexture& mt);


    };
}