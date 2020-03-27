#include <iostream>

#include "usls/App.h"

#include "BootSceneHeadless.h"



void BootSceneHeadless::load()
{
    // Add a stage. The value returned will be the index value of the stage in the scene.
    int stageId = this->addStage(); // create a stage and retrieve it's index
    auto& stage = this->getStage(stageId);
    stage.loadActors("data/models/bin/stages/004/004.fbx"); // add actors to this stage, use default shader for all meshes in this file

    std::cout << "Loaded Actors:" << stage.getActorSize();

}


void BootSceneHeadless::loop()
{
    // Application logic, move things around, etc
    
}

void BootSceneHeadless::end()
{
    // What to do when this scene is over
}