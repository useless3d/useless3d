#include "inc/Stage.h"
#include "inc/AssetLoader.h"

namespace usls
{

    Stage::Stage(std::string file)
    {
        AssetLoader::loadStage(file, this);
    }
    Stage::~Stage() {}

    void Stage::addProp() 
    {
        
    }

    int Stage::getNumProps()
    {
        return this->props.size();
    }

}