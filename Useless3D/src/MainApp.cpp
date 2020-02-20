#include "inc/MainApp.h"
#include "usls/inc/Stage.h"
#include "usls/inc/Camera.h"
#include "usls/inc/PerspectiveCamera.h"

void MainApp::init()
{
    std::unique_ptr<usls::Camera> camera1 =
        std::make_unique<usls::PerspectiveCamera>(
            &this->window.getScreenSize(),
            usls::Camera::Projection::PERSPECTIVE,
            usls::Camera::ViewSpace::WORLD,
            0.1f,
            250.0f,
            45.0f
        );

    this->addStage("stage1", std::move(camera1));
    this->stages.back()->addProp("data/models/bin/stages/003FBX/003.fbx");

}


void MainApp::perFrameLogic()
{
    // Application logic, move things around, etc
    //usls::Scene* scene = usls::Scene::get();
    


}
