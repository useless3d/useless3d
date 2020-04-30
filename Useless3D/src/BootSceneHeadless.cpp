#include <iostream>

#include "usls/App.h"

#include "BootSceneHeadless.h"



void BootSceneHeadless::load()
{
    // Add a stage. The value returned will be the index value of the stage in the scene.
    auto& stage = this->addStage(); // create a stage and retrieve it's index
    stage.loadActors("data/models/bin/maps/004/004.fbx"); // add actors to this stage, use default shader for all meshes in this file

	stage.loadActor("data/models/bin/characters/t_01/t_01.fbx");
	auto skinnedActor = stage.getActor("t_01");
	skinnedActor->animate("run_no_gun");
	skinnedActor->getTransform().setTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

    std::cout << "Loaded Actors:" << stage.getActorSize() << "\n";

}


void BootSceneHeadless::loop()
{
    // Application logic, move things around, etc
    
}