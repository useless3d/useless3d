#include <iostream>

#include "usls/App.h"
#include "usls/scene/stage/Controller.h"



namespace usls::scene::stage
{

	Controller::Controller() :
		input(App::get().getInputState())
	{}



}