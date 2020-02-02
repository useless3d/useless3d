#include "inc/Window.h"

namespace usls
{
    Window::Window(glm::vec2* screenSize, InputState* input, bool fullscreen) : 
        screenSize(screenSize),
        input(input),
        fullscreen(fullscreen)
    {

        // Initialize GLFW. This is the library that creates our cross platform (kinda since
        // apple decided to ditch opengl support for metal only) window object
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // stutter caused when not in fullscreen mode: https://stackoverflow.com/a/21663076/1609485
        // https://www.reddit.com/r/opengl/comments/8754el/stuttering_with_learnopengl_tutorials/dwbp7ta?utm_source=share&utm_medium=web2x
        // could be because of multiple monitors all running different refresh rates

        if (!this->fullscreen) {
            this->glfwWindow = glfwCreateWindow(this->screenSize->x, this->screenSize->y, "Useless3D", NULL, NULL);
        }
        else {
            this->glfwWindow = glfwCreateWindow(this->screenSize->x, this->screenSize->y, "Useless3D", glfwGetPrimaryMonitor(), NULL);
        }

        if (this->glfwWindow == NULL) {

            this->initFailed = true;
            this->initMessage = "Failed to create GLFW window";
            glfwTerminate();

        }
        else {

            glfwMakeContextCurrent(this->glfwWindow);

            // Initialize glad. Glad is a .c file which is included in our project.
            // GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

                this->initFailed = true;
                this->initMessage = "Failed to initialize GLAD";

            }
            else {

                // Associate this object with the window
                glfwSetWindowUserPointer(this->glfwWindow, this);

                // Set callback functions used by glfw (for when polling is unavailable or it makes better sense
                // to use a callback)
                setCallbacks();

                // Set window input mode
                //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

                // Set opengl viewport size
                glViewport(0, 0, this->screenSize->x, this->screenSize->y);

            }

        }


    }
    Window::~Window() {

        glfwDestroyWindow(this->glfwWindow);

        // Terminate GLFW application process
        glfwTerminate();

    }

    void Window::setCallbacks() {

        // Scroll
        glfwSetScrollCallback(this->glfwWindow, [](GLFWwindow* window, double xoffset, double yoffset) {

            // get this from window
            void* data = glfwGetWindowUserPointer(window);
            Window* w = static_cast<Window*>(data);
            w->scrollX = xoffset;
            w->scrollY = yoffset;

        });

        // Window size updated
        glfwSetFramebufferSizeCallback(this->glfwWindow, [](GLFWwindow* window, int width, int height) {

            // get this from window
            void* data = glfwGetWindowUserPointer(window);
            Window* w = static_cast<Window*>(data);
            w->screenSize->x = width;
            w->screenSize->y = height;

            glViewport(0, 0, width, height);

        });

    }

    void Window::update() {

        // this method is invoked every tick

        // check if any events are triggered
        glfwPollEvents();

        setKeys();
        setMouse();
        setScroll();

    }


    void Window::swapBuffers() {

        // swap the color buffer (a large buffer that contains color values for each pixel in GLFW's window) 
        // that has been used to draw in during this iteration and show it as output to the screen
        glfwSwapBuffers(this->glfwWindow);

    }


    double Window::time() {

        return glfwGetTime();

    }


    bool Window::getInitFailed() {

        return initFailed;

    }

    std::string Window::getInitMessage() {

        return initMessage;

    }

    bool Window::shouldClose() {

        return glfwWindowShouldClose(this->glfwWindow);

    }

    void Window::setKeys() {

        this->input->keyEsc = glfwGetKey(this->glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS;
        this->input->keyW = glfwGetKey(this->glfwWindow, GLFW_KEY_W) == GLFW_PRESS;
        this->input->keyA = glfwGetKey(this->glfwWindow, GLFW_KEY_A) == GLFW_PRESS;
        this->input->keyS = glfwGetKey(this->glfwWindow, GLFW_KEY_S) == GLFW_PRESS;
        this->input->keyD = glfwGetKey(this->glfwWindow, GLFW_KEY_D) == GLFW_PRESS;
        this->input->keySpace = glfwGetKey(this->glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS;

    }

    void Window::setMouse() {

        glfwGetCursorPos(this->glfwWindow, &this->input->mouseXPos, &this->input->mouseYPos);

    }

    void Window::setScroll() {

        this->input->scrollX = scrollX;
        this->input->scrollY = scrollY;
        scrollX = 0;
        scrollY = 0;

    }

    void Window::setToClose() {

        glfwSetWindowShouldClose(this->glfwWindow, true);

    }
}