#include "inc/Scene.h"

#include "inc/App.h"

namespace usls
{
    Scene::Scene() :
        shader(Shader(App::get()->config.SHADER_FILE_PATH, App::get()->config.DEFAULT_VERTEX_SHADER, App::get()->config.DEFAULT_FRAGMENT_SHADER)) // initialize as the default shader
    {

    }

    /*
    * Add a headless stage
    */
    void Scene::addStage(std::string stageName)
    {
        auto newStage = std::make_unique<Stage>(stageName);
        this->stages.push_back(std::move(newStage));
    }

    /*
    * Add a NON-headless stage. Since camera is passed we know the user intends for this to be a renderable stage.
    * However this will be overwritten if the state of the app is set to headless.
    */
    void Scene::addStage(std::string stageName, std::unique_ptr<Camera> camera)
    {
        auto newStage = std::make_unique<Stage>(stageName, std::move(camera));
        this->stages.push_back(std::move(newStage));
    }

    void Scene::draw()
    {
        // TODO: Interpolation of all Stage Actors (this will require a fair amout of restructuring of how
        // we are currently drawing renderables)

        // Draw all stages in order they were created (layered)
        for (auto& s : this->stages)
        {
            s->draw(&this->shader);
        }

        
    }

}