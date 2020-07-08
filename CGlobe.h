#pragma once

#include "GameSDL.h"
#include "Log.h"
#include "TetrisDlg.h"

class CGlobe
{
private:

public:
	static BOOL KEY_UP;
	static BOOL KEY_DOWN;
	static BOOL KEY_LEFT;
	static BOOL KEY_RIGHT;
	static BOOL KEY_PAUSE;

	static CTetrisDlg* dlg;

	CGlobe() {
		GameSDL::InitGame();
	}

	~CGlobe() {
		GameSDL::QuitGame();
		lena::Log::uninit();
	}
};

extern CGlobe Globe;
