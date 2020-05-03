#pragma once

#include "usls/scene/Scene.h"


class ExampleScene2 : public usls::scene::Scene
{

public:
	ExampleScene2() : usls::scene::Scene() {};

	void    load();
	void    loop();


};