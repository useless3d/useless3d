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
			// create window
            auto w = std::make_unique<Window>(this->config.SCREEN_WIDTH, this->config.SCREEN_HEIGHT, this->config.FULLSCREEN);
            this->window = std::move(w);

			// initialize GPU
			this->gpu = GPU(this->config.SHADER_FILE_PATH);

			// create default shader
            this->gpu->loadShader("default", this->config.DEFAULT_VERTEX_SHADER, this->config.DEFAULT_FRAGMENT_SHADER);

			// create default texture
			this->gpu->loadTexture("diffuse", ("data/models/bin/default_texture.jpg"));

        }
    }

    void App::setScene(std::unique_ptr<Scene> scene)
    {
        this->scene = std::move(scene);
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

    const glm::ivec2& App::getScreenSize() const
    {
        return this->window.value()->getScreenSize();
    }

    const InputState& App::getInputState() const
    {
        return this->window.value()->getInputState();
    }

    void App::clearScene()
    {
        this->scene.reset();
    }

    std::optional<GPU>& App::getGPU()
    {
        return this->gpu;
    }

    void App::displayAverageFrameTime()
    {
        if (this->time() - this->lastDisplayTime >= 1.0 && this->averageFrameTimeArrayFull) 
        {    
            this->lastDisplayTime = this->time();

            double average = 0.0;
            for (auto& v : this->averageFrameTimeArray)
            {
                average += v;
            }

            average = average / 100.0;
            
            this->window.value()->setTitle("FrameTime: " + std::to_string(average) + " | FPS: " + std::to_string(1000 / (average * 1000)));
        }

        this->averageFrameTimeArray[this->currentAverageFrameTimeArrayIndex] = this->frameTime;

        if (this->currentAverageFrameTimeArrayIndex == 99)
        {
            if (!this->averageFrameTimeArrayFull)
            {
                this->averageFrameTimeArrayFull = true;
            }
            this->currentAverageFrameTimeArrayIndex = 0;

            return;
        }
        
        this->currentAverageFrameTimeArrayIndex++;
    }

    void App::execute()
    {
        this->deltaTime = 1 / this->config.LOGIC_TICK;
        this->currentTime = this->time();

        //this->window.value()->printAddress();

        while (true)
        {
            this->displayAverageFrameTime();            

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
                    
                    if (this->scene && this->scene.value()->loaded) 
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