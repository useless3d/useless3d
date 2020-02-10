#pragma once

#include <chrono>

#include <glm/glm.hpp>
#include "InputState.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace usls
{

    class Window
    {
       
    private:
        glm::vec2*		screenSize;
        InputState*		input;
        GLFWwindow*     glfwWindow;
        bool            initFailed = false;
        std::string		initMessage = "ok";
        int				screenWidth;
        int				screenHeight;
        double			scrollX = 0;
        double			scrollY = 0;
        bool            fullscreen = false;


        void			setKeys();
        void			setMouse();
        void			setScroll();
        void			setCallbacks();

    public:
        Window(glm::vec2* screenSize, InputState* input, bool fullscreen);
        ~Window();
        bool			getInitFailed();
        std::string		getInitMessage();
        bool			shouldClose();
        void			setToClose();
        void			update();
        double			time();


        void			swapBuffers();
        //void			vsync();
    };
    
    
};
