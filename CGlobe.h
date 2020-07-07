#pragma once

#include "GameSDL.h"
#include "Log.h"

class CGlobe
{
private:

public:
	static bool KEY_UP;
	static bool KEY_DOWN;
	static bool KEY_LEFT;
	static bool KEY_RIGHT;
	static bool KEY_PAUSE;
	CGlobe() {
		GameSDL::InitGame();
	}

	~CGlobe() {
		GameSDL::QuitGame();
		lena::Log::uninit();
	}

	static void SetKeyAllFalse() {
		KEY_UP = false;
		KEY_DOWN = false;
		KEY_LEFT = false;
		KEY_RIGHT = false;
		KEY_PAUSE = false;
	}
};

extern CGlobe Globe;
