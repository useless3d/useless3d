#include <iostream>

#include "usls/scene/Stage.h"




namespace usls
{

    Stage::Stage()
    {

    }

    Stage::Stage(std::string cameraName) :
        cameraName(cameraName)
    {
        
    }

    void Stage::addActor(Actor* a)
    {
        this->actors.push_back(a);
    }

    const std::string Stage::getCameraName() const
    {
        if (this->cameraName)
        {
            return this->cameraName.value();
        }
        else
        {
            std::cout << "Attempting to get cameraName from a Stage that does not have a camera\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }
    }

}