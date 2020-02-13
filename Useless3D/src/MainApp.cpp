#include "inc/MainApp.h"

#include <iostream>
#include "usls/inc/Scene.h"
#include "usls/inc/Config.h"
#include "usls/inc/Stage.h"

void MainApp::init()
{
    usls::Scene* scene = usls::Scene::get();
    scene->addStage("TestStage","data/models/bin/stages/003FBX/003.fbx", 
        usls::ProjectionType::PERSPECTIVE, usls::ViewSpace::WORLD);

    //std::cout << "Props:" << scene->getStagePropCount("TestStage") << "\n";
    //std::cout << "Meshes:" << scene->getTotalMeshCount() << "\n";
    


}


void MainApp::logicLoop()
{
    // Application logic, move things around, etc
    //usls::Scene* scene = usls::Scene::get();
    

}
