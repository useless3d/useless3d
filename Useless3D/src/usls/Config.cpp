#include "inc/Config.h"
#include "inc/Logger.h"

#include "inc/helpers.h"

#include <fstream>
#include <sstream>

#include <iostream>

namespace usls
{
    Config::Config(std::string userConfigPath) :
        userConfigParams(this->loadFromFile(userConfigPath)),
        /*SCREEN_WIDTH(userConfigParams.contains("screenWidth") ? std::stoi(this->userConfigParams["screenWidth"]) : 1280),
        SCREEN_HEIGHT(userConfigParams.contains("screenHeight") ? std::stoi(this->userConfigParams["screenHeight"]) : 720),
        FULLSCREEN(userConfigParams.contains("fullScreen") ? (this->userConfigParams["fullScreen"] == "0" ? false : true) : false),
        MAX_RENDER_FPS(userConfigParams.contains("maxFps") ? std::stoi(this->userConfigParams["maxFps"]) : 240)*/
        SCREEN_WIDTH(userConfigParams.count("screenWidth") != 0 ? std::stoi(this->userConfigParams["screenWidth"]) : 1280),
        SCREEN_HEIGHT(userConfigParams.count("screenHeight") != 0 ? std::stoi(this->userConfigParams["screenHeight"]) : 720),
        FULLSCREEN(userConfigParams.count("fullScreen") != 0 ? (this->userConfigParams["fullScreen"] == "0" ? false : true) : false),
        MAX_RENDER_FPS(userConfigParams.count("maxFps") != 0 ? std::stod(this->userConfigParams["maxFps"]) : 240)
    {
        
    };

    std::map<std::string, std::string> Config::loadFromFile(std::string path)
    {
        std::ifstream conf;
        try
        {
            conf.open(path); // not throwing error when file path incorrect

            if (!conf.is_open()) 
            {
                std::cout << "Failed to load config.ini file at path: " << path << "\n";
                std::cin.get();
                exit(EXIT_FAILURE);
            }

            std::map<std::string, std::string> returnMap;

            std::string line;
            while (std::getline(conf, line))
            {
                std::istringstream iss(line);
                std::vector<std::string> e = explode_string(iss.str(), '=');
                returnMap[e[0]] = e[1];
            }

            return returnMap;

        }
        catch (std::ifstream::failure e)
        {
            std::cout << "Failed to load config.ini file at path: " << e.what() << "\n";
            std::cin.get();
            exit(EXIT_FAILURE);
        }
    }

}