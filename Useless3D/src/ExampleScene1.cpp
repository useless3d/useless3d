#include <iostream>

#include "usls/App.h"



#include "BootScene.h"
#include "ExampleScene1.h"


void ExampleScene1::load()
{
    // Add a stage. The value returned will be the index value of the stage in the scene.
    int stageId = this->addStage(); // create a stage and retrieve it's index
    auto& stage = this->getStage(stageId);
    stage.addPerspectiveCamera(false, 0.1f, 250.0f, 45.0f); // add a camera to the stage
    stage.getCamera()->setPosition(0.0f, 4.0f, 8.0f);
    stage.getCamera()->setLookAt(0.0f, 0.0f, 0.0f);
    stage.loadActors("data/models/bin/stages/004/004.fbx"); // add actors to this stage, use default shader for all meshes in this file
    //this->getStage(stageId).loadActors("data/models/bin/stages/005/005.fbx", 3); // add actors to this stage, use given shader id for all meshis in this file
    //this->getStage(stageId).loadActors("data/models/bin/stages/005/005.fbx", { // add actors to this stage, use a vector of pairs where first value is the id of the shader and second value is a vector of strings containing patterns of actor names of which should use this shader index
    //    { 1,{ "obj1", "anotherObject2", "someName" } },
    //    { 2,{ "obj4", "obj5", "obj6", "etc" } }
    //});




    
    // Create a second stage that will be rendered on top of the previous stage

    //this->addOrthographicCamera("camera2", true, -0.1f, 250.0f, 0.665f);
    //this->addStage("stage2", "camera2");
    //this->addActor("stage2", "data/models/bin/stages/005/005.fbx");


    //this->addActor("stage2", "data/models/bin/stages/005/005.fbx") // default shader
    //this->addActor("stage2", "data/models/bin/stages/005/005.fbx", 3) // use shader with index name for all objects created from this file
    

}


void ExampleScene1::loop()
{
    // Application logic, move things around, swap scenes, etc

    if (usls::App::get().getInputState().keySpace) {
        this->end();
    }

}

void ExampleScene1::end()
{
    // What to do when this scene is over

    //usls::App::get().setScene(std::move(std::make_unique<BootScene>()));
}
