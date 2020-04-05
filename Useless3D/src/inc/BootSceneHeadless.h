#pragma once

#include "usls/scene/Scene.h"


class BootSceneHeadless : public usls::scene::Scene
{

public:
    BootSceneHeadless() : usls::scene::Scene() {};

    void    load();
    void    loop();

};