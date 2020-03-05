

#include "usls/App.h"
#include "usls/scene/stage/camera/PerspectiveCamera.h"
#include "usls/scene/stage/camera/OrthographicCamera.h"

#include "ExampleScene1.h"
#include "BootScene.h"


void BootScene::load()
{
    std::unique_ptr<usls::Camera> camera2 = std::make_unique<usls::OrthographicCamera>(
        true, // fixed (transformations relative to camera viewspace, not worldspace when true)
        -0.1f, // near plane
        250.0f, // far plane
        0.665f); // scale

    this->addStage("stage1", std::move(camera2));
    this->stages.back()->addProp("data/models/bin/stages/boot/boot.fbx");

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

    usls::App::get().setScene(std::move(std::make_unique<ExampleScene1>()));
}