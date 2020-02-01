#pragma once

#include <chrono>


#include "InputState.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace usls
{

    class Window
    {
       
    private:

        GLFWwindow*     window;
        bool            initFailed = false;
        std::string		initMessage;
        int				screenWidth;
        int				screenHeight;
        double			scrollX = 0;
        double			scrollY = 0;


        void			setKeys();
        void			setMouse();
        void			setScroll();
        void			setCallbacks();

    public:
        Window();
        ~Window();
        bool			getInitFailed();
        std::string		getInitMessage();
        bool			shouldClose();
        void			setToClose();
        void			update();
        double			time();


        void			swapBuffers();
        void			vsync();
    };
    
    
};
