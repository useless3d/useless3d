#pragma once

#include "usls/scene/Scene.h"


class ExampleScene1 : public usls::scene::Scene
{

public:
    ExampleScene1() : usls::scene::Scene() {};

    void    load();
    void    loop();
    

};