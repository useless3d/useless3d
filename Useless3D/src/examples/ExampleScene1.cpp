#include <iostream>

#include "usls/App.h"


#include "examples/BootScene.h"
#include "examples/ExampleScene1.h"

/*
	Used to test and verify functionality during development, so
	things will be everywhere and may not make sense. As functionality becomes
	more concrete, there will be designated individual Scene files which demonstrate
	various features.
*/

void ExampleScene1::load()
{
    // Add an additional shader program
    //int myShaderIndex = this->addShader("test1", "test1.vert", "test1.frag");


    // Add a stage.
    auto& stage = this->addStage();


	// Add camera to stage and set it's position, and direction (look at)
    stage.addPerspectiveCamera(false, 0.1f, 250.0f, 45.0f);
    stage.getCamera()->setPosition(0.0f, 3.0f, 6.0f);
    stage.getCamera()->setLookAt(0.0f, 1.0f, -1.0f);


	// Add static actors that make up the environment
	stage.loadActors("data/models/bin/maps/004/004.fbx"); // add actors to this stage, use default shader for all meshes in this file
	//stage.loadActors("data/models/bin/maps/004/004.fbx", myShaderIndex); // add actors to this stage, use given shader id for all meshes in this file
	//stage.loadActors("data/models/bin/maps/004/004.fbx", { // add actors to this stage, use a vector of pairs where first value is the id of the shader and second value is a vector of strings containing patterns of actor names of which should use this shader index
	//    { myShaderIndex, { "crate.01", "crate.02" } }
	//});

    
	// Add an animated (skinned) actor reposition, and set to animate
	stage.loadActor("data/models/bin/characters/t_01/t_01.fbx");
	stage.loadActor("data/models/bin/characters/t_01/ak47.fbx");
	//stage.loadActor("data/models/bin/characters/sphere/sphere.fbx");

	auto skinnedActor = stage.getActor("t_01");
	skinnedActor->animate("run_gun_down");
	skinnedActor->translate(glm::vec3(0.0f, 0.0f, 0.0f));
	skinnedActor->rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	stage.parentActorToActorBone("ak47", "t_01", "Bip01 R Hand");


    // Create a second stage that will be rendered on top of the previous stage
    auto& stage2 = this->addStage();
    stage2.addOrthographicCamera(true, -0.1f, 250.0f, 0.665f);
    stage2.loadActors("data/models/bin/maps/005/005.fbx");
	

}


void ExampleScene1::loop()
{
    // Application logic, move things around, swap scenes, etc

	if (usls::App::get().getInputState().keyEsc)
	{
		usls::App::get().close();
	}

	//auto& stage = this->getStage(0);

    //if (usls::App::get().getInputState().keySpace) 
    //{
    //    usls::App::get().setScene(std::move(std::make_unique<BootScene>()));
    //}

}