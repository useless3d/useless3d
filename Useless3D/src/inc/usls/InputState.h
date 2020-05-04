#pragma once

namespace usls
{
    struct InputState
    {
        bool	keyW = false;
        bool	keyA = false;
        bool	keyS = false;
        bool	keyD = false;
        bool	keyEsc = false;
        bool	keySpace = false;
		bool	keyUp = false;
		bool	keyDown = false;
		bool	keyRight = false;
		bool	keyLeft = false;
        double	mouseXPos = 0;
        double	mouseYPos = 0;
        double	scrollX = 0;
        double	scrollY = 0;
    };
}

