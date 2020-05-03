#include <iostream>

#include "usls/App.h"
#include "examples/TerminateController.h"


void TerminateController::logic()
{
	if (this->input.keyEsc)
	{
		usls::App::get().close();
	}

}