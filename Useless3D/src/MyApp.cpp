#include "inc/MyApp.h"

#include <iostream>

MyApp::MyApp(usls::Ini ini) : usls::App(ini){}
MyApp::~MyApp() {}

void MyApp::logicLoop() 
{
    std::cout << "YEEEEEAAAAAAHhhhh\n";
    std::cout << this->ini.maxFps;
}
