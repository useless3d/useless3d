#pragma once

#include "usls/inc/Config.h"
#include "usls/inc/App.h"

class MainApp : public usls::App
{

public:
    MainApp(usls::Config config) : usls::App(config) {};
    ~MainApp() {};
    void    logicLoop();
    void    init();

};