#include <iostream>
#include <memory>

#include "inc/MainApp.h"

int main()
{
    // Bootstrap MainApp
    MainApp app(false); // false means we are not running headless
    app.execute();
    return 0;
}