#include "inc/MainApp.h"

#include <iostream>
#include "usls/inc/Scene.h"
#include "usls/inc/Config.h"
#include "usls/inc/Stage.h"
#include "usls/inc/Camera.h"

void MainApp::init()
{

    usls::Scene* scene = usls::Scene::get();
    scene->addStage("TestStage","data/models/bin/stages/003FBX/003.fbx", 
    //scene->addStage("TestStage", "data/models/bin/stages/003DAE/003.dae",
        usls::ProjectionType::PERSPECTIVE, usls::ViewSpace::WORLD);

    std::cout << "Props:" << scene->getStagePropCount("TestStage") << "\n";
    std::cout << "Meshes:" << scene->getTotalMeshCount() << "\n";
    
    usls::Camera* camera = usls::Camera::get();
    camera->setPosition(glm::vec3(0.0f, 6.0f, 10.0f));
    camera->setDirection(glm::vec3(0.0f, 0.0f, 0.0f));
    camera->update();

}


void MainApp::logicLoop()
{
    // Application logic, move things around, etc
    //usls::Scene* scene = usls::Scene::get();
    


}
