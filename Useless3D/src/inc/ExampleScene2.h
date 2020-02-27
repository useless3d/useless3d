#pragma once

#include "usls/inc/Scene.h"


class ExampleScene2 : public usls::Scene
{

public:
    ExampleScene2() : usls::Scene() {};

    void    load();
    void    loop();
    void    end();

};