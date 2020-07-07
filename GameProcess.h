#pragma once
#include <WinSock2.h>
#include"GameManager.h"
#include "Bricks.h"
#include "GameSDL.h"

#define Singlescore 100

class GameProcess {
public:
	GameManager TetrisManger;
	GameSDL* GameDraw;
	int score=0;
	int n;//用于判断是否自动下落；

	GameProcess(GameSDL* A) {
		GameDraw = A;
	}
	BOOL TranslateMessage(MSG* pMSG);
	void OnBnClickBegin();
	UINT BeginGame(LPVOID param);
	void DrawMap(int x, int y, int type, int state, SingleSquare bcgSquare[WidthBySquare][HeightBySquare + 4]);
	void BeginGame();
	BOOL Around();
};
