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
        
    }
    App::~App() {}

    /*
    * Add a headless stage
    */
    void App::addStage(std::string stageName)
    {
        this->stages.push_back(Stage(stageName));
    }

    /*
    * Add a NON-headless stage. Since ProjectionType and ViewSpace are passed we know the user
    * intends for this to be a renderable stage. However this will be overwritten if the state of the app
    * is set to headless.
    */
    void App::addStage(std::string stageName, ProjectionType projType, ViewSpace vSpace) 
    {
        this->stages.push_back(Stage(stageName, projType, vSpace));
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
                //usls::Scene::get()->draw();

                this->window.swapBuffers();

            }

        }
    }

}