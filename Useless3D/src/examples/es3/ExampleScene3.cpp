#include <iostream>
#include <memory>

#include "usls/App.h"


#include "examples/es3/ExampleScene3.h"
#include "examples/TerminateController.h"


void ExampleScene3::load()
{

	auto& mainStage = this->addStage();

	this->mainStage->addPerspectiveCamera(false, 0.1f, 250.0f, 45.0f);
	this->mainStage->getCamera()->setPosition(0.0f, 1.0f, 8.0f);
	this->mainStage->getCamera()->setLookAt(0.0f, 0.0f, 0.0f);

	this->mainStage->loadActor("data/models/bin/characters/sphere/sphere.fbx");

	this->mainStage->addController(std::move(std::make_unique<TerminateController>()));



}