#include <iostream>

#include "usls/App.h"


#include "examples/BootScene.h"
#include "examples/ExampleScene2.h"

/*
Used to test and verify functionality during development, so
things will be everywhere and may not make sense. As functionality becomes
more concrete, there will be designated individual Scene files which demonstrate
various features.
*/

void ExampleScene2::load()
{
	// Add a stage.
	auto& stage = this->addStage();


	// Add camera to stage and set it's position, and direction (look at)
	stage.addPerspectiveCamera(false, 0.1f, 250.0f, 45.0f);
	stage.getCamera()->setPosition(0.0f, 3.0f, 5.0f);
	stage.getCamera()->setLookAt(0.0f, 1.0f, -2.0f);


	// Add an animated (skinned) actor, reposition, and set to animate
	stage.loadActor("data/models/bin/characters/t_01/t_01.fbx");
	stage.loadActor("data/models/bin/characters/t_01/ak47.fbx");


	auto skinnedActor = stage.getActor("t_01");
	skinnedActor->animate("run_gun_down");
	skinnedActor->translate(glm::vec3(0.0f, 0.0f, 0.0f));
	skinnedActor->rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	stage.parentActorToActorBone("ak47", "t_01", "Bip01 R Hand");


	// Add 100 skinned animated models with child objects parented to a bone
	size_t tmpId = 10000;
	for (size_t i = 1; i < 20; i++)
	{
		std::string newActorName = "t_01" + std::to_string(tmpId);
		std::string newAkName = "ak47" + std::to_string(tmpId);
		tmpId--;

		auto actorCopy = *stage.getActor("t_01");
		actorCopy.translate(glm::vec3(0.0f, 0.0f, -(float)i * 1.5f));
		actorCopy.setName(newActorName);
		stage.addActor(actorCopy);
		auto akCopy = *stage.getActor("ak47");
		akCopy.setName(newAkName);
		stage.addActor(akCopy);
		stage.parentActorToActorBone(newAkName, newActorName, "Bip01 R Hand");

		newActorName = "t_01" + std::to_string(tmpId);
		newAkName = "ak47" + std::to_string(tmpId);
		tmpId--;
		actorCopy = *stage.getActor("t_01");
		actorCopy.translate(glm::vec3(1.5f, 0.0f, -(float)i * 1.5f));
		actorCopy.setName(newActorName);
		stage.addActor(actorCopy);
		akCopy = *stage.getActor("ak47");
		akCopy.setName(newAkName);
		stage.addActor(akCopy);
		stage.parentActorToActorBone(newAkName, newActorName, "Bip01 R Hand");

		newActorName = "t_01" + std::to_string(tmpId);
		newAkName = "ak47" + std::to_string(tmpId);
		tmpId--;
		actorCopy = *stage.getActor("t_01");
		actorCopy.translate(glm::vec3(-1.5f, 0.0f, -(float)i *  1.5f));
		actorCopy.setName(newActorName);
		stage.addActor(actorCopy);
		akCopy = *stage.getActor("ak47");
		akCopy.setName(newAkName);
		stage.addActor(akCopy);
		stage.parentActorToActorBone(newAkName, newActorName, "Bip01 R Hand");

		newActorName = "t_01" + std::to_string(tmpId);
		newAkName = "ak47" + std::to_string(tmpId);
		tmpId--;
		actorCopy = *stage.getActor("t_01");
		actorCopy.translate(glm::vec3(3.0f, 0.0f, -(float)i * 1.5f));
		actorCopy.setName(newActorName);
		stage.addActor(actorCopy);
		akCopy = *stage.getActor("ak47");
		akCopy.setName(newAkName);
		stage.addActor(akCopy);
		stage.parentActorToActorBone(newAkName, newActorName, "Bip01 R Hand");

		newActorName = "t_01" + std::to_string(tmpId);
		newAkName = "ak47" + std::to_string(tmpId);
		tmpId--;
		actorCopy = *stage.getActor("t_01");
		actorCopy.translate(glm::vec3(-3.0f, 0.0f, -(float)i * 1.5f));
		actorCopy.setName(newActorName);
		stage.addActor(actorCopy);
		akCopy = *stage.getActor("ak47");
		akCopy.setName(newAkName);
		stage.addActor(akCopy);
		stage.parentActorToActorBone(newAkName, newActorName, "Bip01 R Hand");

	}

}


void ExampleScene2::loop()
{
	// Application logic, move things around, swap scenes, etc
	if (usls::App::get().getInputState().keyEsc)
	{
		usls::App::get().close();
	}

}