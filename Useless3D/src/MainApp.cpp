#include "inc/MainApp.h"

#include <iostream>
#include "usls/inc/Stage.h"

void MainApp::init()
{
    usls::Scene* scene = usls::Scene::get();
    scene->addStage("TestStage","data/models/bin/stages/003FBX/003.fbx", 
        usls::ProjectionType::PERSPECTIVE, usls::ViewSpace::WORLD);
    
    usls::Camera* camera = usls::Camera::get();
    camera->setPosition(glm::vec3(0.0f, 6.0f, 10.0f));
    camera->setDirection(glm::vec3(0.0f, 0.0f, 0.0f));
    camera->update();

}


void MainApp::perFrameLogic()
{
    // Application logic, move things around, etc
    //usls::Scene* scene = usls::Scene::get();
    


}
