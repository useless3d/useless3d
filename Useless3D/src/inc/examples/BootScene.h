#pragma once

#include "usls/scene/Scene.h"


class BootScene : public usls::scene::Scene
{

public:
    BootScene() : usls::scene::Scene() {};

    void    load();
    void    loop();

};