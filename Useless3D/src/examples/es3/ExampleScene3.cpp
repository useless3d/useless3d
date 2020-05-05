#include <iostream>
#include <memory>

#include "usls/App.h"


#include "examples/es3/ExampleScene3.h"
#include "examples/TerminateController.h"
#include "examples/es3/ActorController.h"


void ExampleScene3::load()
{

	/*auto& mainStage = this->addStage();

	mainStage.addPerspectiveCamera(false, 0.1f, 250.0f, 45.0f);
	mainStage.getCamera()->setPosition(0.0f, 1.0f, 8.0f);
	mainStage.getCamera()->setLookAt(0.0f, 0.0f, 0.0f);

	mainStage.loadActors("data/models/bin/characters/sphere/sphere.fbx", true);

	auto sphere = mainStage.getActor("sphere");

	mainStage.addController(new ActorController(sphere));
	mainStage.addController(new TerminateController());*/


	auto& mainStage = this->addStage();

	mainStage.addPerspectiveCamera(false, 0.1f, 250.0f, 45.0f);
	mainStage.getCamera()->setPosition(0.0f, 1.0f, 8.0f);
	mainStage.getCamera()->setLookAt(0.0f, 0.0f, 0.0f);

	mainStage.loadActors("data/models/bin/characters/low_poly/low_poly_animated.fbx", true);

	auto character = mainStage.getActor("character");
	character->animate("walk_002");
	

	mainStage.addController(new ActorController(character));
	mainStage.addController(new TerminateController());


}