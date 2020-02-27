#pragma once

#include "usls/inc/Scene.h"


class ExampleScene : public usls::Scene
{

public:
    ExampleScene() : usls::Scene() {};

    void    load();
    void    loop();
    

};