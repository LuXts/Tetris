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
	int x=1;//判断当前的游戏状态（1表示继续下落，2表示到底，3表示在顶端）

	GameProcess(GameSDL* A) {
		GameDraw = A;
	}
	BOOL TranslateMessage(MSG* pMSG);
	void OnBnClickBegin();
	UINT BeginGame(LPVOID param);
	void DrawMap(int x, int y, int type, int state, SingleSquare bcgSquare[WidthBySquare][HeightBySquare + 4]);
	//BOOL BeginGame();
	BOOL Around();//一个方块的游戏流程
	BOOL InitBrick();//将方块移动到最上端；
};
