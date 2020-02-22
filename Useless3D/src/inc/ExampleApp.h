#pragma once

#include "usls/inc/Config.h"
#include "usls/inc/App.h"

class ExampleApp : public usls::App
{

public:
    ExampleApp(bool headless) : usls::App(headless) {};
    void    perFrameLogic();
    void    init();

};