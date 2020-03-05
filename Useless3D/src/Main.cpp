#include <memory>

#include "usls/App.h"

#include "BootScene.h"


int main()
{
    // Bootstrap an App
    usls::App::init();

    // Load the initial Scene
    std::unique_ptr<usls::Scene> scene = std::make_unique<BootScene>();
    usls::App::get().setScene(std::move(scene));

    // Execute the program, passing control to the App execute loop
    usls::App::get().execute();

    return 0;
}