

#include "usls/App.h"
#include "usls/scene/camera/PerspectiveCamera.h"
#include "usls/scene/camera/OrthographicCamera.h"

#include "BootScene.h"
#include "ExampleScene1.h"


void ExampleScene1::load()
{
    // Create camera and set initial position and lookat vectors
    //std::unique_ptr<usls::Camera> camera1 =
    //    std::make_unique<usls::PerspectiveCamera>(
    //        false, // fixed (transformations relative to worldspace when false)
    //        0.1f, // near plane
    //        250.0f, // far plane
    //        45.0f); // FOV
    //camera1->setPosition(glm::vec3(0.0f, 4.0f, 8.0f));
    //camera1->setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));

    this->addPerspectiveCamera("camera1", false, 0.1f, 250.0f, 45.0f);
    this->cameras["camera1"]->setPosition(glm::vec3(0.0f, 4.0f, 8.0f));
    this->cameras["camera1"]->setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));


    // Create a stage
    //this->addStage("stage1", std::move(camera1));
    //this->stages.back()->addProp("data/models/bin/stages/004/004.fbx");

    this->addStage("stage1", "camera1");

    // Add actors
    this->addActor("stage1", "data/models/bin/stages/005/005.fbx");


    std::unique_ptr<usls::Camera> camera2 = std::make_unique<usls::OrthographicCamera>(
            true, // fixed (transformations relative to camera viewspace, not worldspace when true)
            -0.1f, // near plane
            250.0f, // far plane
            0.665f); // scale

    this->addStage("stage2", std::move(camera2));
    this->stages.back()->addProp("data/models/bin/stages/005/005.fbx");

    //this->addStage("stage2", std::move(camera2));
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
