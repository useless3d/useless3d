#include <iostream>
#include "App.h"

namespace usls
{
    
    App::App(Ini ini) : 
        ini(ini),
        screenSize(glm::vec2(this->ini.screenWidth, this->ini.screenHeight)), 
        window(Window(&this->screenSize, &this->input, this->ini.fullScreen))
    {

        if (this->window.getInitFailed()) {
            this->initFailed = true;
            this->initMessage = this->window.getInitMessage();
        }
        else {



        }

    }
    App::~App() {}

    bool App::getInitFailed() 
    {
        return this->initFailed;
    }

    std::string App::getInitMessage()
    {
        return this->initMessage;
    }

}