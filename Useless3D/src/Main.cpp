#include <iostream>

#include "usls/inc/Config.h"
#include "inc/MainApp.h"
#include <memory>

int main()
{

    std::unique_ptr<MainApp>    app = std::make_unique<MainApp>();
    app->execute();


    std::cout << "\nEND\n";
    std::cin.get();
    return 0;
}