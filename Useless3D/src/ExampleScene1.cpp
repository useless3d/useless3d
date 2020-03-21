#include <iostream>

#include "usls/App.h"



#include "BootScene.h"
#include "ExampleScene1.h"


void ExampleScene1::load()
{
    // Add a stage
    this->addStage(1); // create a stage with the given integer id (used for lookup)

    // Add a camera to the stage
    this->getStage(1).addPerspectiveCamera(false, 0.1f, 250.0f, 45.0f);

    // Add actors to this stage (Scene is responsible for adding actors to a stage as it holds data that can be shared between stages)
    this->addActors(this->getStage(1), "data/models/bin/stages/005/005.fbx"); // use default shader for all meshes in this file



    
    // Create a second stage that will be rendered on top of the previous stage

    //this->addOrthographicCamera("camera2", true, -0.1f, 250.0f, 0.665f);
    //this->addStage("stage2", "camera2");
    //this->addActor("stage2", "data/models/bin/stages/005/005.fbx");


    //this->addActor("stage2", "data/models/bin/stages/005/005.fbx") // default shader
    //this->addActor("stage2", "data/models/bin/stages/005/005.fbx", "shader1") // use shader with specified name for all objects created from this file
    //this->addActor("stage2", "data/models/bin/stages/005/005.fbx", {"obj1", 1, "obj2", 2}) // use vector of strings where each even element is a pattern of a name of an object (so "obj1" would match "obj1.001" and "obj1.002", etc) and each odd element is the id of a shader program to be used for processing the object that matches the name of the even element prior to itself

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

    usls::App::get().setScene(std::move(std::make_unique<BootScene>()));
}
