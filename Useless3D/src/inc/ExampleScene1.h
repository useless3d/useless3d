#pragma once

#include "usls/inc/Scene.h"


class ExampleScene1 : public usls::Scene
{

public:
    ExampleScene1() : usls::Scene() {};

    void    load();
    void    loop();
    void    end();
    

};