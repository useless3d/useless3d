#pragma once

#include "usls/inc/Scene.h"
#include "usls/inc/App.h"

class ExampleScene : public usls::Scene
{

public:
    ExampleScene(usls::App* const app) : usls::Scene(app) {};

    void    load();
    void    loop();
    

};