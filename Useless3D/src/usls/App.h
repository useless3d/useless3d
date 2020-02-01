#pragma once

#include <glm/glm.hpp>
#include "InputState.h"
//#include "Window.h"
//#include "Scene.h"

namespace usls 
{
    
    class App
    {
    public:
        App();
        ~App();
        glm::vec2       screenSize;
        InputState      input;
        //Window          window;
        //Scene           scene;
             
        


    };

};
