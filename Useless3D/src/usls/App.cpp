#include <iostream>

#include "usls/App.h"


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
        startTime(std::chrono::high_resolution_clock::now())
    {
        if (!this->config.HEADLESS)
        {
            auto w = std::make_unique<Window>(this->config.SCREEN_WIDTH, this->config.SCREEN_HEIGHT, this->config.FULLSCREEN);
            this->window = std::move(w);

            this->gpu = GPU(this->config.SHADER_FILE_PATH);
            this->gpu->loadShader("default", this->config.DEFAULT_VERTEX_SHADER, this->config.DEFAULT_FRAGMENT_SHADER);
        }
    }
    
    Scene* App::getScene()
    {
        return this->scene.value().get();
    }

    void App::close()
    {
        this->shouldClose = true;
        if (!this->config.HEADLESS) 
        {
            this->window.value()->setToClose();
        }
    }

    const double App::time() const
    {
        std::chrono::duration<double> t = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - this->startTime);
        return t.count();
    }

    const glm::vec2& App::getScreenSize() const
    {
        return this->window.value()->getScreenSize();
    }

    const InputState& App::getInputState() const
    {
        return this->window.value()->getInputState();
    }

    void App::setScene(std::unique_ptr<Scene> scene)
    {
        this->scene = std::move(scene);
    }

    void App::clearScene()
    {
        this->scene.reset();
    }

    std::optional<GPU>& App::getGPU()
    {
        return this->gpu;
    }

    void App::execute()
    {
        this->deltaTime = 1 / this->config.LOGIC_TICK;
        this->currentTime = this->time();

        //this->window.value()->printAddress();

        while (true)
        {
            if (this->shouldClose || (!this->config.HEADLESS && this->window.value()->shouldClose())) 
            {
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
                        this->window.value()->update();
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
                    this->gpu->enableDepthTest();
                    //this->gpu->drawLinesOnly();
                    this->gpu->clearBuffers(0.2f, 0.3f, 0.3f, 1.0f);

                    if (this->scene && this->scene.value()->loaded)
                    {
                        this->scene.value()->draw();
                    }

                    this->window.value()->swapBuffers();
                }
                

            }

        }
    }

}