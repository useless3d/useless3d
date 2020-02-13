#include "inc/Stage.h"
#include "inc/AssetLoader.h"

namespace usls
{

    Stage::Stage(std::string file, ProjectionType pType, ViewSpace vSpace) :
        pType(pType),
        vSpace(vSpace)
    {
        AssetLoader::loadStage(file, this);
    }
    Stage::~Stage() 
    {
        
    }

    void Stage::addProp(Prop prop) 
    {
        this->props.push_back(prop);
    }

    int Stage::getNumProps()
    {
        return this->props.size();
    }

    std::vector<Prop> Stage::getProps()
    {
        return this->props;
    }

}