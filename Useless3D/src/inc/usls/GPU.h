#pragma once


#include "usls/scene/mesh/Mesh.h"
#include "usls/scene/mesh/MeshTexture.h"


namespace usls
{
    class GPU
    {
    public:
        void loadMesh(Mesh& m);
        void loadTexture(MeshTexture& mt);
    };
}