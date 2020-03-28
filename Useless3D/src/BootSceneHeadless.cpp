#include <iostream>

#include "usls/App.h"

#include "BootSceneHeadless.h"



void BootSceneHeadless::load()
{
    // Add a stage. The value returned will be the index value of the stage in the scene.
    auto& stage = this->addStage(); // create a stage and retrieve it's index
    stage.loadActors("data/models/bin/stages/004/004.fbx"); // add actors to this stage, use default shader for all meshes in this file

    std::cout << "Loaded Actors:" << stage.getActorSize();

}


void BootSceneHeadless::loop()
{
    // Application logic, move things around, etc
    
}