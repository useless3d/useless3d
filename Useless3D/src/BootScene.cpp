#include <iostream>

#include "usls/App.h"
#include "usls/scene/camera/OrthographicCamera.h"


#include "ExampleScene1.h"
#include "BootScene.h"


void BootScene::load()
{
    this->addOrthographicCamera("camera1", true, -0.1f, 250.0f, 0.665f);
    this->addStage("stage1", "camera1");
    this->addActor("stage1", "data/models/bin/stages/boot/boot.fbx");



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
    std::cout << "resetting scene\n";
    usls::App::get().setScene(std::move(std::make_unique<ExampleScene1>()));
}