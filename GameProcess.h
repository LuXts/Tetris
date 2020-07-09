#pragma once
#include <WinSock2.h>
#include"GameManager.h"
#include "Bricks.h"
#include "GameSDL.h"

#define Singlescore 100

class GameProcess {
private:
	GameSDL* GameDraw;
public:
	GameManager TetrisManger;
	int score = 0;

	GameProcess(GameSDL* A);
	void DrawMap(int x, int y, int type, int state, SingleSquare bcgSquare[WidthBySquare][HeightBySquare]);
	void DrawNext();

	BOOL Around();
};
