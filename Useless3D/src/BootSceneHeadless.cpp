#include <iostream>

#include "usls/App.h"

#include "BootSceneHeadless.h"



void BootSceneHeadless::load()
{

    this->addStage("stage1");
    this->addActor("stage1", "data/models/bin/stages/005/005.fbx");

    //std::cout << "Props:" << this->stages.back()->getPropCount() << "\n";
    //std::cout << "Meshes:" << this->stages.back()->getMeshCount() << "\n";

}


void BootSceneHeadless::loop()
{
    // Application logic, move things around, etc
    
}

void BootSceneHeadless::end()
{
    // What to do when this scene is over
}