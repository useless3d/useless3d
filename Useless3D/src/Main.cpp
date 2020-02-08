#include <iostream>

#include "usls/inc/Ini.h"
#include "inc/MyApp.h"

int main()
{

    usls::Ini   ini;
    MyApp       app(ini);

    app.execute();


    std::cout << "\nEND\n";
    std::cin.get();
    return 0;
}