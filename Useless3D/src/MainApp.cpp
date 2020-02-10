#include "inc/MainApp.h"

#include <iostream>
#include "usls/inc/Scene.h"

void MainApp::init()
{
    auto scene = std::make_unique<usls::Scene>();
    scene->setStage("data/models/bin/stages/003FBX/003.fbx");
    
    

}


void MainApp::logicLoop()
{
    std::cout << "YEEEEEAAAAAAHhhhh\n";
    std::cout << this->config.maxFps;
}
