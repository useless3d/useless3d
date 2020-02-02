#pragma once

#include <glm/glm.hpp>
#include "InputState.h"
#include "Window.h"
#include "Ini.h"
//#include "Scene.h"

namespace usls 
{
    
    class App
    {
    private:
        Ini             ini;
    public:
        glm::vec2       screenSize;
    private:
        Window          window;
        bool            initFailed = false;
        std::string     initMessage = "ok";
        //Scene           scene;

    public:       
        InputState      input;
        App(Ini ini);
        ~App();
        bool            getInitFailed();
        std::string     getInitMessage();

    };

};
