#include <iostream>
#include <memory>

#include "inc/ExampleScene.h"
#include "usls/inc/App.h"

int main()
{
    // Bootstrap an App
    usls::App::init();

    // Load the initial Scene
    std::unique_ptr<usls::Scene> scene = std::make_unique<ExampleScene>();
    usls::App::get()->setScene(std::move(scene));
    usls::App::get()->execute();


    return 0;
}