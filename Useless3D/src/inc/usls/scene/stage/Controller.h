#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"


#include "usls/InputState.h"


namespace usls::scene::stage
{
	class Controller
	{
	protected:
		const InputState&	input;
		double				deltaTime;

	public:
							Controller();
		void				setDeltaTime(double delta);
		virtual void		logic() = 0;
	};
}