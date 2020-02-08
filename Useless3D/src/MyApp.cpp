#include "inc/MyApp.h"

#include <iostream>
#include "usls/inc/Scene.h"

void MyApp::init()
{
    auto scene = std::make_unique<usls::Scene>();
    scene->setStage("data/models/bin/stages/003FBX/003.fbx");
    std::cout << usls::Mesh::getMeshCount();
}


void MyApp::logicLoop() 
{
    std::cout << "YEEEEEAAAAAAHhhhh\n";
    std::cout << this->ini.maxFps;
}
