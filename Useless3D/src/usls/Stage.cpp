#include "inc/Stage.h"
#include "inc/AssetLoader.h"

namespace usls
{

    Stage::Stage(std::string file)
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

}