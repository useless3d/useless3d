#include "inc/MainApp.h"

#include <iostream>
#include "usls/inc/Scene.h"
#include "usls/inc/Config.h"

void MainApp::init()
{
    usls::Scene* scene = usls::Scene::get();
    scene->setStage("data/models/bin/stages/003FBX/003.fbx");
    


}


void MainApp::logicLoop()
{
    std::cout << "YEEEEEAAAAAAHhhhh\n";
    std::cout << usls::Config::get()->maxFps;
}
