#include <iostream>
#include <memory>

#include "usls/App.h"


#include "examples/es3/ExampleScene3.h"
#include "examples/TerminateController.h"
#include "examples/es3/SphereController.h"


void ExampleScene3::load()
{

	auto& mainStage = this->addStage();

	mainStage.addPerspectiveCamera(false, 0.1f, 250.0f, 45.0f);
	mainStage.getCamera()->setPosition(0.0f, 1.0f, 8.0f);
	mainStage.getCamera()->setLookAt(0.0f, 0.0f, 0.0f);

	mainStage.loadActor("data/models/bin/characters/sphere/sphere.fbx");

	auto sphere = mainStage.getActor("sphere");
	sphere->setDynamic(true);


	mainStage.addController(new SphereController(sphere));
	mainStage.addController(new TerminateController());


}