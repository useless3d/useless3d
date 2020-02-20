#pragma once

#include <string>
#include <vector>

namespace usls
{
    class Config
    {
    private:
        std::vector<std::string> explode(std::string const & s, char delim);

        bool                logEnabled;
        std::string         logPath;
        int                 screenWidth;
        int                 screenHeight;
        bool                fullScreen;
        int                 maxFps;

    public:
        Config(std::string configPath);
        
        const std::string   SHADER_FILE_PATH = "Useless3D/src/usls/shaders";
        const std::string   DEFAULT_VERTEX_SHADER = "default.vert";
        const std::string   DEFAULT_FRAGMENT_SHADER = "default.frag";

        const bool& getLogEnabled() const;
        const std::string& getLogPath() const;
        const int& getScreenWidth() const;
        const int& getScreenHeight() const;
        const bool& getFullScreen() const;
        const int& getMaxFps() const;


    };
}