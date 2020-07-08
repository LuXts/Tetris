#pragma once

#include "GameSDL.h"
#include "Log.h"

class CGlobe
{
private:

public:
	static BOOL KEY_UP;
	static BOOL KEY_DOWN;
	static BOOL KEY_LEFT;
	static BOOL KEY_RIGHT;
	static BOOL KEY_PAUSE;
	CGlobe() {
		GameSDL::InitGame();
	}

	~CGlobe() {
		GameSDL::QuitGame();
		lena::Log::uninit();
	}

	static void SetKeyAllFALSE() {
		KEY_UP = FALSE;
		KEY_DOWN = FALSE;
		KEY_LEFT = FALSE;
		KEY_RIGHT = FALSE;
		KEY_PAUSE = FALSE;
	}
};

extern CGlobe Globe;
