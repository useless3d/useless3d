#pragma once

#include "usls/inc/Config.h"
#include "usls/inc/App.h"

class MainApp : public usls::App
{

public:
    MainApp() : usls::App() {};
    ~MainApp() {};
    void    perFrameLogic();
    void    init();

};