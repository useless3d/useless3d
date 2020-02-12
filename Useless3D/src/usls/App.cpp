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

            this->deltaTime = 1 / this->logicTick;
            this->currentTime = this->window.time();

            


        }

    }
    App::~App() {}

    void App::execute()
    {
        this->init();
        //this->logicLoop();
    }

}