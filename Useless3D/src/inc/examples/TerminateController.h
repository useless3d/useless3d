#pragma once

#include "usls/scene/stage/Controller.h"


class TerminateController : public usls::scene::stage::Controller
{

public:
	TerminateController() : usls::scene::stage::Controller() {};
	void    logic();
};