#include <iostream>

#include "usls/App.h"



#include "ExampleScene1.h"
#include "BootScene.h"


void BootScene::load()
{
    //this->addOrthographicCamera("camera1", true, -0.1f, 250.0f, 0.665f);
    //this->addStage("stage1", "camera1");
    //this->addActor("stage1", "data/models/bin/stages/boot/boot.fbx");

    // Add a stage. The value returned will be the index value of the stage in the scene.
    int stageId = this->addStage(); // create a stage and retrieve it's index
    auto& stage = this->getStage(stageId);
    stage.addOrthographicCamera(true, -0.1f, 250.0f, 0.665f); // add a camera to the stage
    stage.loadActors("data/models/bin/stages/boot/boot.fbx"); // add actors to this stage, use default shader for all meshes in this file

}


void BootScene::loop()
{
    // Application logic, move things around, etc
    if (usls::App::get().getInputState().keySpace) {
        this->end();
    }
}

void BootScene::end()
{
    // What to do when this scene is over
    //std::cout << "resetting scene\n";
    usls::App::get().setScene(std::move(std::make_unique<ExampleScene1>()));
}