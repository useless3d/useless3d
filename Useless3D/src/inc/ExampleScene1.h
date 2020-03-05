#pragma once

#include "usls/scene/Scene.h"


class ExampleScene1 : public usls::Scene
{

public:
    ExampleScene1() : usls::Scene() {};

    void    load();
    void    loop();
    void    end();
    

};