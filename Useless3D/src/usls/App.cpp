#include <iostream>
#include "inc/App.h"
#include "inc/Logger.h"

#include <iostream>

namespace usls
{

    /*
        Since there can only ever be a single instance of App (vital for windowing and user input),
        App is implemented as a singleton and initialized as the first step in Main.cpp. This also
        allows for access to App's members from any class which might require them without App needing
        to be explicitly passed as a parameter (keeping api clean for users).

        I'm still not entirely sold on this however since it's introducing a global state object into
        the codebase. If anyone sees this and has a more elegant solution, I'm all ears!
    */
    App* App::instance = 0;
    
    void App::init(bool headless)
    {
        App::instance = new App(headless); // This feels dirty
    }

    App* App::get()
    {
        if (App::instance == 0) {
            App::init(false);
        }
        return App::instance;
    }


    App::App(bool headless) : 
        headless(headless),
        config(Config("data/config.ini")),
        window(Window(this->config.getScreenWidth(), this->config.getScreenHeight(), this->config.getFullScreen())),
        maxFps((double)this->config.getMaxFps())
    {
        // Enable logging
        if (this->config.getLogEnabled()) 
        {
            Logger::enable(this->config.getLogPath());
        }

        // If window is not successfully created, log message and exit
        if (this->window.getInitFailed()) 
        {
            if (Logger::isEnabled()) 
            {
                Logger::log(this->window.getInitMessage());
            }
            exit(EXIT_FAILURE);
        }

        //std::cout << this->window.time() << "\n";
        
    }
    

    void App::close()
    {
        this->shouldClose = true;
        if (!this->headless) {
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
        this->deltaTime = 1 / this->logicTick;
        this->currentTime = this->time();

        while (true)
        {
            if (this->shouldClose || (!this->headless && this->window.shouldClose())) {
                break;
            }


            if (this->scene && !this->scene.value()->loaded)
            {
                this->scene.value()->load();
                this->scene.value()->loaded = true;
            }

            this->newTime = this->time();
            this->frameTime = this->newTime - this->currentTime;

            if (this->frameTime >= (1 / this->maxFps)) // cap max fps
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
                    if (!this->headless) 
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
                if (!this->headless)
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