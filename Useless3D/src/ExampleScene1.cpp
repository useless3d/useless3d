

#include "usls/App.h"
#include "usls/scene/camera/PerspectiveCamera.h"
#include "usls/scene/camera/OrthographicCamera.h"

#include "BootScene.h"
#include "ExampleScene1.h"


void ExampleScene1::load()
{
    // Add a camera
    this->addPerspectiveCamera("camera1", false, 0.1f, 250.0f, 45.0f);
    this->cameras["camera1"]->setPosition(glm::vec3(0.0f, 4.0f, 8.0f));
    this->cameras["camera1"]->setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));

    // Add a stage
    this->addStage("stage1", "camera1");

    // Add actors
    this->addActor("stage1", "data/models/bin/stages/004/004.fbx");

    
    // Create a second stage that will be rendered on top of the previous stage

    this->addOrthographicCamera("camera2", true, -0.1f, 250.0f, 0.665f);
    this->addStage("stage2", "camera2");
    this->addActor("stage2", "data/models/bin/stages/005/005.fbx");


    //this->addActor("stage2", "data/models/bin/stages/005/005.fbx") // default shader
    //this->addActor("stage2", "data/models/bin/stages/005/005.fbx", "shader1") // use shader with specified name for all objects created from this file
    //this->addActor("stage2", "data/models/bin/stages/005/005.fbx", {"obj1", "shader1", "obj2", "shader2"}) // use vector of strings where each even index is a pattern of a name of an object (so "obj1" would match "obj1.001" and "obj1.002", etc) and each odd index is the name of a shader program to be used for processing the object that matches the name of the even index prior to itself 

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
