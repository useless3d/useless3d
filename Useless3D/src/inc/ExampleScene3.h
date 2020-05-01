#pragma once

#include "usls/scene/Scene.h"
#include "usls/scene/stage/Stage.h"


class ExampleScene3 : public usls::scene::Scene
{

public:
	ExampleScene3() : usls::scene::Scene() {};

	void    load();
	void    loop();

	usls::scene::stage::Stage* mainStage;

};