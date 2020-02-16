#include <iostream>
#include <memory>

#include "inc/MainApp.h"

int main()
{
    // Bootstrap MainApp
    std::unique_ptr<MainApp>    app = std::make_unique<MainApp>();
    app->execute();
    return 0;
}