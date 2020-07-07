#pragma once
#include <WinSock2.h>
#include"GameManager.h"
#include "Bricks.h"
#include "GameSDL.h"



class GameProcess {
public:
	GameManager TetrisManger;
	GameSDL* GameDraw;

	GameProcess(GameSDL* A) {
		GameDraw = A;
	}
	BOOL TranslateMessage(MSG* pMSG);
	void OnBnClickBegin();
	UINT BeginGame(LPVOID param);
	void DrawMap(int x, int y, int type, int state);
};
