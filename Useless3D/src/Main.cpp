#include <memory>

#include "usls/App.h"

#include "BootScene.h"


int main()
{
    // Bootstrap an App
    usls::App::init();

    // Load the initial Scene
    usls::App::get().setScene(std::move(std::make_unique<BootScene>()));

    // Execute the program, passing control to the App execute loop
    usls::App::get().execute();

    return 0;
}