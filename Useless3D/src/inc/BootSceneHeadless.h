#pragma once

#include "usls/inc/Scene.h"


class BootSceneHeadless : public usls::Scene
{

public:
    BootSceneHeadless() : usls::Scene() {};

    void    load();
    void    loop();
    void    end();

};