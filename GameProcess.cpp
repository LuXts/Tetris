#include "pch.h"

#include "GameProcess.h"
#include "GameManager.h"
#include "SingleSquare.h"
#include "Bricks.h"
#include <afxwin.h>
#include "CGlobe.h"

GameProcess::GameProcess(GameSDL* A) {
	GameDraw = A;
}

UINT GameProcess::BeginGame(LPVOID param) {
	GameProcess* ptask = (GameProcess*)param;
	while (1) {
		ptask->TetrisManger.NewRound();//随机产生一个方块；
		/*此处为绘制右边提示栏“下一个方块”*/
		/*此处为绘制此时的地图（方块出现在屏幕上）*/
		Sleep(500);
		/*
		//检测是否到达底端
		while ( ) {
		ptask->TetrisManger.MoveDown();//向下移动一格
		//此处为绘制此时的地图
		Sleep(500);
		}
		//检测是否到达底端
		if () {
			ptask->TetrisManger.FixBricks();//将方块写入地图
			ptask->TetrisManger.RowCheck();//检测是否成行消去
		}
		///*检测是否到达顶部
		if () {
			return 0;
		}
		*/
	}
	return 0;
}
void GameProcess::DrawMap(int x, int y, int type, int state, SingleSquare bcgSquare[WidthBySquare][HeightBySquare]) {
	GameDraw->MainRendererClear();
	GameDraw->MainAddBrick(x + bricks[type][state].p[0].x, y + bricks[type][state].p[0].y);
	GameDraw->MainAddBrick(x + bricks[type][state].p[1].x, y + bricks[type][state].p[1].y);
	GameDraw->MainAddBrick(x + bricks[type][state].p[2].x, y + bricks[type][state].p[2].y);
	GameDraw->MainAddBrick(x + bricks[type][state].p[3].x, y + bricks[type][state].p[3].y);
	for (int i = 0; i < WidthBySquare; i++) {
		for (int j = 0; j < HeightBySquare; j++) {
			if (bcgSquare[i][j].state == 1) {
				GameDraw->MainAddBrick(i, j);
			}
		}
	}
	GameDraw->MainRendererPresent();
}
BOOL GameProcess::Around() {
	static int time_up = 0;
	static int time_left = 0;
	static int time_right = 0;
	static int time_down = 0;
	static int time_down_max = 50;
	static int time_down_temp = 50;

	if (Globe.KEY_UP == TRUE && time_up-- == 0) {
		Globe.KEY_UP = FALSE;
		TetrisManger.RotateTop();
		time_up = 5;
	}
	if (Globe.KEY_LEFT == TRUE && time_left-- == 0) {
		Globe.KEY_LEFT = FALSE;
		TetrisManger.MoveLeft();
		time_left = 5;
	}
	if (Globe.KEY_RIGHT == TRUE && time_right-- == 0) {
		Globe.KEY_RIGHT = FALSE;
		TetrisManger.MoveRight();
		time_right = 5;
	}
	if (Globe.KEY_DOWN == TRUE) {
		if (time_down_max != 1) {
			time_down_temp = time_down_max;
		}
		time_down_max = 1;
		if (time_down > time_down_max) {
			time_down = 1;
		}
		/*
		if (!TetrisManger.MoveDown()) {
			TetrisManger.FixBricks();
			score = score + (TetrisManger.RowCheck() * TetrisManger.RowCheck()) * Singlescore;
			if (TetrisManger.TopCheck(TetrisManger.centre, bricks[TetrisManger.brickType][TetrisManger.brickState])) {
				x = 3;
				n = 0;
				DrawMap(-5, -5, 1, 1, TetrisManger.bcgSquare);
				return TRUE;
			}//检测是否到顶端
			x = 2;
			n = 0;
			DrawMap(-5, -5, 1, 1, TetrisManger.bcgSquare);
			return TRUE;
		}//检测是否到底端
		*/
	}
	else {
		time_down_max = time_down_temp;
	}
	//n = n + 1;
	//if (n == 30) {
	if (time_down-- == 0) {
		if (!TetrisManger.MoveDown()) {
			/*
			if (TetrisManger.TopCheck(TetrisManger.centre, bricks[TetrisManger.brickType][TetrisManger.brickState])) {
				//x = 3;
				//n = 0;
				//DrawMap(-5, -5, 1, 1, TetrisManger.bcgSquare);
				//return TRUE;
			}                          //检测是否到顶端
			*/
			//x = 2;
			//n = 0;
			//DrawMap(-5, -5, 1, 1, TetrisManger.bcgSquare);
			//return TRUE;
			TetrisManger.FixBricks();
			int temp = TetrisManger.RowCheck();
			score = score + (temp * temp) * Singlescore;
			TetrisManger.NewRound();
		}
		time_down = time_down_max;
	}
	//}
	//x = 1;
	DrawMap(TetrisManger.centre.x, TetrisManger.centre.y, TetrisManger.brickType, TetrisManger.brickState, TetrisManger.bcgSquare);
	return TRUE;
}
BOOL GameProcess::InitBrick() {
	while (1) {
		for (int i = 0; i < 4; i++) {
			if (bricks[TetrisManger.brickState][TetrisManger.brickType].p[i].y == 0) {
				return TRUE;
			}
		}
		TetrisManger.MoveDown();
	}
}//将方块调整到最上面一层