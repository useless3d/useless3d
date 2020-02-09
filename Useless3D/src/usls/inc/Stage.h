#pragma once

#include <vector>
#include "Mesh.h"
#include "Prop.h"
#include <string>

namespace usls
{
    class Stage
    {
    private:
        std::vector<Prop>       props;

    public:
        Stage(std::string file);
        ~Stage();
        void                addProp(Prop prop);
        int                 getNumProps();
    };
}