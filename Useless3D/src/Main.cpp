#include <iostream>

#include "usls/inc/Config.h"
#include "inc/MainApp.h"
#include <memory>

int main()
{

    usls::Config                config;
    std::unique_ptr<MainApp>    app = std::make_unique<MainApp>(config);
    app->execute();


    std::cout << "\nEND\n";
    std::cin.get();
    return 0;
}