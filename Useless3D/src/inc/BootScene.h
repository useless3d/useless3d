#pragma once

#include "usls/scene/Scene.h"


class BootScene : public usls::Scene
{

public:
    BootScene() : usls::Scene() {};

    void    load();
    void    loop();
    void    end();

};