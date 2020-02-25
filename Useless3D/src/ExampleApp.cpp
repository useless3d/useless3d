#include "inc/ExampleApp.h"
#include "usls/inc/Stage.h"
#include "usls/inc/Camera.h"
#include "usls/inc/PerspectiveCamera.h"
#include "usls/inc/OrthographicCamera.h"

#include <iostream>

void ExampleApp::init()
{
    // Create camera and set initial position and lookat vectors
    std::unique_ptr<usls::Camera> camera1 =
        std::make_unique<usls::PerspectiveCamera>(
            &this->window.getScreenSize(), // must always be the address of the window screenSize property (Window updates on resize)
            false, // fixed (transformations relative to worldspace when false)
            0.1f, // near plane
            250.0f, // far plane
            45.0f); // FOV
    camera1->setPosition(glm::vec3(0.0f, 4.0f, 8.0f));
    camera1->setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));

    this->addStage("stage1", std::move(camera1));
    this->stages.back()->addProp("data/models/bin/stages/004/004.fbx");


    std::unique_ptr<usls::Camera> camera2 = std::make_unique<usls::OrthographicCamera>(
            &this->window.getScreenSize(), // must always be the address of the window screenSize property (Window updates on resize)
            true, // fixed (transformations relative to camera viewspace, not worldspace when true)
            -0.1f, // near plane
            250.0f, // far plane
            0.665f); // scale

    this->addStage("stage2", std::move(camera2));
    this->stages.back()->addProp("data/models/bin/stages/005/005.fbx");

}


void ExampleApp::perFrameLogic()
{
    // Application logic, move things around, etc
}
