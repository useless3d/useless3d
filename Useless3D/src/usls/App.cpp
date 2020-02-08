#include <iostream>
#include "inc/App.h"
#include "inc/Logger.h"

namespace usls
{
    
    App::App(Ini ini) : 
        ini(ini),
        screenSize(glm::vec2(this->ini.screenWidth, this->ini.screenHeight)), 
        window(Window(&this->screenSize, &this->input, this->ini.fullScreen)),
        maxFps((double)this->ini.maxFps),
        logicTick((double)this->ini.logicTick)
    {
        // Enable logging
        if (this->ini.logEnabled) {
            Logger::enable(this->ini.logPath);
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