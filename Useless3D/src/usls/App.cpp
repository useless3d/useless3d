#include <iostream>
#include "inc/App.h"
#include "inc/Logger.h"

namespace usls
{
    App::App(bool headless) : 
        headless(headless),
        config(Config("config.ini")),
        window(Window(this->config.getScreenWidth(), this->config.getScreenHeight(), this->config.getFullScreen())),
        maxFps((double)this->config.getMaxFps())
    {
        // Enable logging
        if (this->config.getLogEnabled()) 
        {
            Logger::enable(this->config.getLogPath());
        }

        // If window is not successfully created, log message and exit
        if (this->window.getInitFailed()) 
        {
            if (Logger::isEnabled()) 
            {
                Logger::log(this->window.getInitMessage());
            }
            exit(EXIT_FAILURE);
        }

        this->shader = Shader(config.SHADER_FILE_PATH, config.DEFAULT_VERTEX_SHADER, config.DEFAULT_FRAGMENT_SHADER);
        
    }
    App::~App() {}

    /*
    * Add a headless stage
    */
    void App::addStage(std::string stageName)
    {
        auto newStage = std::make_unique<Stage>(stageName);
        this->stages.push_back(std::move(newStage));
    }

    /*
    * Add a NON-headless stage. Since camera is passed we know the user intends for this to be a renderable stage. 
    * However this will be overwritten if the state of the app is set to headless.
    */
    void App::addStage(std::string stageName, std::unique_ptr<Camera> camera)
    {
        auto newStage = std::make_unique<Stage>(stageName, std::move(camera));
        this->stages.push_back(std::move(newStage));
    }

    const InputState& App::getInputState() const
    {
        return this->window.getInputState();
    }

    void App::execute()
    {
        this->init();

        this->deltaTime = 1 / this->logicTick;
        this->currentTime = this->window.time();

        while (!this->window.shouldClose())
        {
            this->newTime = this->window.time();
            this->frameTime = this->newTime - this->currentTime;

            if (this->frameTime >= (1 / this->maxFps)) // cap max fps
            {

                this->currentTime = this->newTime;

                // prevent spiral of death
                if (this->frameTime > 0.25)
                {
                    this->frameTime = 0.25;
                }

                this->accumulator += this->frameTime;

                // exit if keyEsc pressed (remove this and let user determine this behaviour in their loop)
                if (this->getInputState().keyEsc)
                {
                    this->window.setToClose();
                    continue;
                }

                // process update logic
                while (this->accumulator >= this->deltaTime)
                {
                    // update window, which includes capturing input state
                    this->window.update();

                    // call user defined perFrameLogic method
                    this->perFrameLogic();

                    // decrement accumulator
                    this->accumulator -= this->deltaTime;
                }

                // perform draw (render) logic with (eventually) automatic interpolation of stage actors
                if (!this->headless)
                {
                    this->draw();
                }
                

            }

        }
    }

    void App::draw()
    {
        // TODO: Interpolation of all Stage Actors


        glEnable(GL_DEPTH_TEST);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Draw only lines for debugging

        // Select a color to clear the screen with and clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw all stages in order they were created (layered)
        for (auto& s : this->stages)
        {
            s->draw(&this->shader);
        }

        this->window.swapBuffers();
    }

}