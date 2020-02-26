#include <iostream>
#include <memory>

#include "inc/ExampleScene.h"

int main()
{
    // Bootstrap an App
    auto app = std::make_unique<usls::App>(false);

    // Load the initial Scene
    std::unique_ptr<usls::Scene> scene = std::make_unique<ExampleScene>(app.get());
    app->setScene(std::move(scene)); // need to use std::move
    app->execute();


    return 0;
}