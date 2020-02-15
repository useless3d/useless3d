#include "inc/Config.h"
#include "inc/Logger.h"

#include <fstream>
#include <sstream>

namespace usls
{
    Config::Config(std::string configPath) 
    {
        std::ifstream conf;

        try
        {
            conf.open(configPath);

            std::string line;
            while (std::getline(conf, line))
            {
                std::istringstream iss(line);
                std::vector<std::string> e = this->explode(iss.str(), '=');

                // Disgusting but works for now. Elegance can come later.
                if (e[0] == "logEnabled")
                    this->logEnabled = e[1] == "1" ? true : false;
                else if (e[0] == "logPath")
                    this->logPath = e[1];
                else if (e[0] == "screenWidth")
                    this->screenWidth = std::stoi(e[1]);
                else if (e[0] == "screenHeight")
                    this->screenHeight = std::stoi(e[1]);
                else if (e[0] == "fullScreen")
                    this->fullScreen = e[1] == "1" ? true : false;
                else if (e[0] == "maxFps")
                    this->maxFps = std::stoi(e[1]);

            }

        }
        catch (std::ifstream::failure e)
        {
            if (Logger::isEnabled()) {
                Logger::log("Failed to load config.ini file");
            }
            
            exit(EXIT_FAILURE);
        }

    };

    std::vector<std::string> Config::explode(std::string const & s, char delim)
    {
        std::vector<std::string> result;
        std::istringstream iss(s);

        for (std::string token; std::getline(iss, token, delim); )
        {
            result.push_back(std::move(token));
        }

        return result;
    }
    
    const bool& Config::getLogEnabled() const
    {
        return this->logEnabled;
    }

    const std::string& Config::getLogPath() const
    {
        return this->logPath;
    }

    const int& Config::getScreenWidth() const
    {
        return this->screenWidth;
    }

    const int& Config::getScreenHeight() const
    {
        return this->screenHeight;
    }

    const bool& Config::getFullScreen() const
    {
        return this->fullScreen;
    }

    const int& Config::getMaxFps() const
    {
        return this->maxFps;
    }

}