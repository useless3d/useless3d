#include <iostream>

#include "usls/App.h"


#include "ExampleScene3.h"


void ExampleScene3::load()
{

	this->mainStage = &this->addStage();

	this->mainStage->addPerspectiveCamera(false, 0.1f, 250.0f, 45.0f);
	this->mainStage->getCamera()->setPosition(0.0f, 1.0f, 8.0f);
	this->mainStage->getCamera()->setLookAt(0.0f, 0.0f, 0.0f);

	this->mainStage->loadActor("data/models/bin/characters/sphere/sphere.fbx");





}


void ExampleScene3::loop()
{
	// Application logic, move things around, swap scenes, etc
	if (usls::App::get().getInputState().keyEsc)
	{
		usls::App::get().close();
	}

	if (usls::App::get().getInputState().keyD)
	{
		


	}


}