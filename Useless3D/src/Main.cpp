#include <iostream>

#include "usls/Ini.h"
#include "usls/App.h"

int main()
{

    usls::Ini   ini;
    usls::App   app(ini);
    if (app.getInitFailed()) {
        std::cout << app.getInitMessage() << std::endl;
    }


    std::cin.get();
    return 0;
}