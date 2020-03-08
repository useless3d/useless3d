#include "usls/scene/mesh/Vertex.h"

namespace usls
{
    bool Vertex::operator==(const Vertex &v) const
    {
        return position == v.position && normal == v.normal && textureCoordinates == v.textureCoordinates;
    }
}