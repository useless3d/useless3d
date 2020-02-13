#pragma once

#include <vector>
#include "Mesh.h"
#include "Prop.h"
#include <string>

namespace usls
{
    enum ProjectionType
    {
        PERSPECTIVE,
        ORTHOGRAPHIC
    };

    enum ViewSpace
    {
        VIEW,
        WORLD
    };

    class Stage
    {
    private:
        std::vector<Prop>       props;
        ProjectionType          pType;
        ViewSpace               vSpace;

    public:
        Stage(std::string file, ProjectionType pType, ViewSpace vSpace);
        ~Stage();
        void                addProp(Prop prop);
        int                 getNumProps();
        std::vector<Prop>   getProps();

    };
}