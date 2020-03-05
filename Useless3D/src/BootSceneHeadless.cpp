#include "usls/inc/App.h"
#include "inc/BootSceneHeadless.h"

#include <iostream>

void BootSceneHeadless::load()
{

    this->addStage("stage1");
    this->stages.back()->addProp("data/models/bin/stages/004/004.fbx");

    std::cout << "Props:" << this->stages.back()->getPropCount() << "\n";
    std::cout << "Meshes:" << this->stages.back()->getMeshCount() << "\n";

}


void BootSceneHeadless::loop()
{
    // Application logic, move things around, etc
    
}

void BootSceneHeadless::end()
{
    // What to do when this scene is over
}