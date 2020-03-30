#include <iostream>

#include "usls/App.h"



#include "BootScene.h"
#include "ExampleScene1.h"


void ExampleScene1::load()
{
    // Add an additional shader program
    int myShaderIndex = this->addShader("test1", "test1.vert", "test1.frag");

    // Add a stage. The value returned will be the index value of the stage in the scene.
    auto& stage = this->addStage(); // create a stage and retrieve it's index
    stage.addPerspectiveCamera(false, 0.1f, 250.0f, 45.0f); // add a camera to the stage
    stage.getCamera()->setPosition(0.0f, 4.0f, 8.0f);
    stage.getCamera()->setLookAt(0.0f, 0.0f, 0.0f);
    stage.loadActors("data/models/bin/stages/004/004.fbx"); // add actors to this stage, use default shader for all meshes in this file
    //stage.loadActors("data/models/bin/stages/004/004.fbx", myShaderIndex); // add actors to this stage, use given shader id for all meshes in this file
    //stage.loadActors("data/models/bin/stages/004/004.fbx", { // add actors to this stage, use a vector of pairs where first value is the id of the shader and second value is a vector of strings containing patterns of actor names of which should use this shader index
    //    { myShaderIndex, { "crate.01", "crate.02" } }
    //});


    // Create a second stage that will be rendered on top of the previous stage
    auto& stage2 = this->addStage();
    stage2.addOrthographicCamera(true, -0.1f, 250.0f, 0.665f); // add a camera to the stage
    stage2.loadActors("data/models/bin/stages/005/005.fbx");
    

}


void ExampleScene1::loop()
{
    // Application logic, move things around, swap scenes, etc
    auto& stage = this->getStage(0);

    if (usls::App::get().getInputState().keySpace) 
    {
        usls::App::get().setScene(std::move(std::make_unique<BootScene>()));
    }

    if (usls::App::get().getInputState().keyD) 
    {
        stage.removeActor("crate.010");
        stage.removeActor("crate.011");
        stage.removeActor("crate.012");
        stage.removeActor("crate.013");
    }

    if (usls::App::get().getInputState().keyA)
    {
        auto actorCopy = stage.getActor("crate");
        actorCopy.getTransform().setTranslation(glm::vec3(0.0f, 0.0f, 0.0f));
        actorCopy.getTransform().setScale(glm::vec3(2.0f, 2.0f, 2.0f));
        stage.addActor(actorCopy);

        stage.printRenderCommands();
    }

}