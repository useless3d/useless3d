#include "usls/scene/mesh/MeshVertex.h"

namespace usls
{
    bool MeshVertex::operator==(const MeshVertex &v) const
    {
        return position == v.position && normal == v.normal && textureCoordinates == v.textureCoordinates;
    }
}