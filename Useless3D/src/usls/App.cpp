#include <iostream>
#include "inc/App.h"

namespace usls
{

    void App::init()
    {
        App::get();
    }
    
    App& App::get()
    {
        static App instance;
        return instance;
    }

    App::App() : 
        config(Config("data/config.ini")),
        logger(this->config.LOG_ENABLED, this->config.LOG_PATH),
        window(Window(this->config.SCREEN_WIDTH, this->config.SCREEN_HEIGHT, this->config.FULLSCREEN))
    {
        
    }
    

    void App::close()
    {
        this->shouldClose = true;
        if (!this->config.HEADLESS) {
            this->window.setToClose();
        }
    }

    const double App::time() const
    {
        return this->window.time(); // use something other than window to obtain this since we will not have a window when running headless
    }

    const glm::vec2& App::getScreenSize() const
    {
        return this->window.getScreenSize();
    }

    const InputState& App::getInputState() const
    {
        return this->window.getInputState();
    }

    void App::setScene(std::unique_ptr<Scene> scene)
    {
        this->scene = std::move(scene);
    }

    void App::clearScene()
    {
        this->scene.reset();
    }

    void App::execute()
    {
        this->deltaTime = 1 / this->config.LOGIC_TICK;
        this->currentTime = this->time();

        while (true)
        {
            if (this->shouldClose || (!this->config.HEADLESS && this->window.shouldClose())) {
                break;
            }


            if (this->scene && !this->scene.value()->loaded)
            {
                this->scene.value()->load();
                this->scene.value()->loaded = true;
            }

            this->newTime = this->time();
            this->frameTime = this->newTime - this->currentTime;

            if (this->frameTime >= (1 / this->config.MAX_RENDER_FPS)) // cap max fps
            {

                this->currentTime = this->newTime;

                // prevent spiral of death
                if (this->frameTime > 0.25)
                {
                    this->frameTime = 0.25;
                }

                this->accumulator += this->frameTime;

                // exit if keyEsc pressed (remove this and let user determine this behaviour in their loop)
                if (this->getInputState().keyEsc)
                {
                    this->close();
                    continue;
                }

                // process update logic
                while (this->accumulator >= this->deltaTime)
                {
                    if (!this->config.HEADLESS)
                    {
                        // update window, which includes capturing input state
                        this->window.update();
                    }
                    
                    if (this->scene) 
                    {
                        // call user defined loop method (where logic is performed (ie movement and such))
                        this->scene.value()->loop();
                    }
                    
                    // decrement accumulator
                    this->accumulator -= this->deltaTime;
                }

                // perform draw (render) logic with (eventually) automatic interpolation of stage actors
                if (!this->config.HEADLESS)
                {
                    glEnable(GL_DEPTH_TEST);
                    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Draw only lines for debugging

                    // Select a color to clear the screen with and clear screen
                    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    if (this->scene)
                    {
                        this->scene.value()->draw();
                    }

                    this->window.swapBuffers();
                }
                

            }

        }
    }

}