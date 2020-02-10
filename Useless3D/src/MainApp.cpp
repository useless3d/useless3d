#include "inc/MainApp.h"

#include <iostream>
#include "usls/inc/Scene.h"

void MainApp::init()
{
    scene->setStage("data/models/bin/stages/003FBX/003.fbx");
    
    

}


void MainApp::logicLoop()
{
    std::cout << "YEEEEEAAAAAAHhhhh\n";
    std::cout << this->config.maxFps;
}
