#include <iostream>
#include "inc/App.h"
#include "inc/Logger.h"

namespace usls
{
    
    App::App(Config config) : 
        config(config),
        screenSize(glm::vec2(this->config.screenWidth, this->config.screenHeight)),
        window(Window(&this->screenSize, &this->input, this->config.fullScreen)),
        maxFps((double)this->config.maxFps),
        logicTick((double)this->config.logicTick),
        scene(std::make_unique<usls::Scene>())
    {
        // Enable logging
        if (this->config.logEnabled) {
            Logger::enable(this->config.logPath);
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