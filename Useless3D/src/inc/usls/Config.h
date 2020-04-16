#pragma once

#include <string>
#include <map>


namespace usls
{
    class Config
    {
    private:
        std::map<std::string, std::string> loadFromFile(std::string path);
        std::map<std::string, std::string> userConfigParams;        

    public:
        Config(std::string userConfigPath);

        // Application defined
        const bool          HEADLESS = false;
        const bool          LOG_ENABLED = true;
        const std::string   LOG_PATH = "data/log.txt";
        const std::string   SHADER_FILE_PATH = "Useless3D/src/usls/scene/shaders";
        const std::string   DEFAULT_VERTEX_SHADER = "skinned.vert";
        const std::string   DEFAULT_FRAGMENT_SHADER = "skinned.frag";
        const double        LOGIC_TICK = 120.0;

        // User defined via config.ini
        const int           SCREEN_WIDTH;
        const int           SCREEN_HEIGHT;
        const bool          FULLSCREEN;
        const double        MAX_RENDER_FPS;
        


    };
}