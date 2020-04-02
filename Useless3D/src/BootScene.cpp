#include <iostream>

#include "usls/App.h"



#include "ExampleScene1.h"
#include "BootScene.h"


void BootScene::load()
{

    // Add a stage. The value returned will be the index value of the stage in the scene.
    auto& stage = this->addStage(); // create a stage
    stage.addOrthographicCamera(true, -0.1f, 250.0f, 0.665f); // add a camera to the stage
    stage.loadActors("data/models/bin/maps/boot/boot.fbx"); // add actors to this stage, use default shader for all meshes in this file

}


void BootScene::loop()
{
    // Application logic, move things around, etc
    if (usls::App::get().getInputState().keySpace) 
    {    
        usls::App::get().setScene(std::move(std::make_unique<ExampleScene1>()));
    }
}