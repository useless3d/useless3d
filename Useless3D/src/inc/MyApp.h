#pragma once

#include "../usls/inc/Ini.h"
#include "../usls/inc/App.h"

class MyApp : public usls::App
{

public:
    MyApp(usls::Ini ini) : usls::App(ini) {};
    ~MyApp() {};
    void    logicLoop();

};