#include <iostream>
#include <memory>

#include "inc/ExampleApp.h"

int main()
{
    // Bootstrap an App
    ExampleApp app(false); // false means we are not running headless
    app.execute();
    return 0;
}