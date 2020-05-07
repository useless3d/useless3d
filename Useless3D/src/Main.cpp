#include <memory>

#include "usls/App.h"

#include "examples/ExampleScene2.h"


int main()
{
    // Bootstrap an App
    usls::App::init();

    // Load the initial Scene
    usls::App::get().setScene(new ExampleScene2());

    // Execute the program, passing control to the App execute loop
    usls::App::get().execute();

    return 0;
}