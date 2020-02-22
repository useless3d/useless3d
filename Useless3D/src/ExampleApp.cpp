#include "inc/ExampleApp.h"
#include "usls/inc/Stage.h"
#include "usls/inc/Camera.h"
#include "usls/inc/PerspectiveCamera.h"
#include "usls/inc/OrthographicCamera.h"

#include <iostream>

void ExampleApp::init()
{
    // Create camera and set initial position and lookat vectors
    //std::unique_ptr<usls::Camera> camera1 =
    //    std::make_unique<usls::PerspectiveCamera>(
    //        &this->window.getScreenSize(), // must always be the address of the window screenSize property
    //        false, // will use camera position and lookat vectors to position elements in world space
    //        0.1f, // near plane
    //        250.0f, // far plane
    //        45.0f); // FOV
    //camera1->setPosition(glm::vec3(0.0f, 6.0f, 10.0f));
    //camera1->setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));




    std::unique_ptr<usls::Camera> camera1 = std::make_unique<usls::OrthographicCamera>(
            &this->window.getScreenSize(), // must always be the address of the window screenSize property
            false, // will use camera position and lookat vectors to position elements in world space
            -1000.0f, // near plane
            1000.0f); // far plane
    camera1->setPosition(glm::vec3(0.0f, 6.0f, 10.0f));
    camera1->setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));




    this->addStage("stage1", std::move(camera1));
    //this->stages.back()->addProp("data/models/bin/stages/003FBX/003.fbx");
    this->stages.back()->addProp("data/models/bin/stages/004/004.fbx");

    //std::cout << "Meshes: " << this->stages.back()->getMeshCount() << "\n";
    //std::cout << "Props: " << this->stages.back()->getPropCount() << "\n";

}


void ExampleApp::perFrameLogic()
{
    // Application logic, move things around, etc
}
