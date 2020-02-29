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
        glm::vec2		screenSize;
        bool            fullScreen = false;
        InputState		inputState;
        GLFWwindow*     glfwWindow;
        double			scrollX = 0.0;
        double			scrollY = 0.0;
        


        void			setKeys();
        void			setMouse();
        void			setScroll();
        void			setCallbacks();

    public:
        Window(int screenWidth, int screenHeight, bool fullScreen);
        ~Window();
        bool			shouldClose();
        void			setToClose();
        void			update();
        const double	time() const;

        const InputState& getInputState() const;
        const glm::vec2& getScreenSize() const;

        void			swapBuffers();
        //void			vsync();
    };
    
    
};
