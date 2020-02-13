#include <iostream>
#include "inc/App.h"
#include "inc/Logger.h"

namespace usls
{
    
    App::App() : 
        screenSize(glm::vec2(Config::get()->screenWidth, Config::get()->screenHeight)),
        window(Window(&this->screenSize, &this->input, Config::get()->fullScreen)),
        maxFps((double)Config::get()->maxFps),
        logicTick((double)Config::get()->logicTick)
    {
        // Enable logging
        if (Config::get()->logEnabled) {
            Logger::enable(Config::get()->logPath);
        }

        // If window is not successfully created, log message and exit
        if (this->window.getInitFailed()) {
            if (Logger::isEnabled()) {
                Logger::log(this->window.getInitMessage());
            }
            exit(EXIT_FAILURE);
        }
        // Window was successfully created, continue initialization
        else {

            // Initialize camera
            Camera::init(&this->screenSize);

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
                    if (this->input.keyEsc)
                    {
                        this->window.setToClose();
                        continue;
                    }

                    // process update logic
                    while (this->accumulator >= this->deltaTime)
                    {
                        // capture input state
                        this->window.update();

                        // call user defined loop
                        this->logicLoop();

                        // decrement accumulator
                        this->accumulator -= this->deltaTime;

                    }

                    // perform draw (render) logic with (eventually) automatic interpolation of stage actors
                    usls::Scene::get()->draw();

                }

            }

            


        }

    }
    App::~App() {}

    void App::execute()
    {
        this->init();
        //this->logicLoop();
    }

}