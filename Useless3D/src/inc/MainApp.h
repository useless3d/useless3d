#pragma once

#include "usls/inc/Config.h"
#include "usls/inc/App.h"

class MainApp : public usls::App
{

public:
    MainApp(bool headless) : usls::App(headless) {};
    ~MainApp() {};
    void    perFrameLogic();
    void    init();

};