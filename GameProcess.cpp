﻿#include "pch.h"

#include "GameProcess.h"
#include "GameManager.h"
#include "SingleSquare.h"
#include "Bricks.h"
#include <afxwin.h>
#include "CGlobe.h"
#include "Log.h"

GameProcess::GameProcess(GameSDL* A) {
	GameDraw = A;
}

void GameProcess::DrawMap(int x, int y, int type, int state, SingleSquare bcgSquare[WidthBySquare][HeightBySquare]) {
	GameDraw->MainRendererClear();
	GameDraw->MainAddBrick(x + bricks[type][state].p[0].x, y + bricks[type][state].p[0].y - 4);
	GameDraw->MainAddBrick(x + bricks[type][state].p[1].x, y + bricks[type][state].p[1].y - 4);
	GameDraw->MainAddBrick(x + bricks[type][state].p[2].x, y + bricks[type][state].p[2].y - 4);
	GameDraw->MainAddBrick(x + bricks[type][state].p[3].x, y + bricks[type][state].p[3].y - 4);
	for (int i = 0; i < WidthBySquare; i++) {
		for (int j = 0; j < HeightBySquare; j++) {
			if (bcgSquare[i][j].state == 1) {
				GameDraw->MainAddBrick(i, j - 4);
			}
		}
	}
	GameDraw->MainRendererPresent();
}

void GameProcess::DrawNext() {
	GameDraw->NextRendererClear();
	GameDraw->NextAddBrick(2 + bricks[TetrisManger.brickNext][0].p[0].x, 2 + bricks[TetrisManger.brickNext][0].p[0].y);
	GameDraw->NextAddBrick(2 + bricks[TetrisManger.brickNext][0].p[1].x, 2 + bricks[TetrisManger.brickNext][0].p[1].y);
	GameDraw->NextAddBrick(2 + bricks[TetrisManger.brickNext][0].p[2].x, 2 + bricks[TetrisManger.brickNext][0].p[2].y);
	GameDraw->NextAddBrick(2 + bricks[TetrisManger.brickNext][0].p[3].x, 2 + bricks[TetrisManger.brickNext][0].p[3].y);
	GameDraw->NextRendererPresent();
}

BOOL GameProcess::Around() {
	static int time_up = 0;
	static int time_left = 0;
	static int time_right = 0;
	static int time_max = 5;
	static int time_down = 0;
	static int time_down_max = 50;
	static int time_down_temp = 50;

	if (Globe.KEY_UP == TRUE && time_up-- == 0) {
		Globe.KEY_UP = FALSE;
		TetrisManger.RotateTop();
		time_up = time_max;
	}
	if (Globe.KEY_LEFT == TRUE && time_left-- == 0) {
		Globe.KEY_LEFT = FALSE;
		TetrisManger.MoveLeft();
		time_left = time_max;
	}
	if (Globe.KEY_RIGHT == TRUE && time_right-- == 0) {
		Globe.KEY_RIGHT = FALSE;
		TetrisManger.MoveRight();
		time_right = time_max;
	}
	if (Globe.KEY_DOWN == TRUE) {
		if (time_down_max != 1) {
			time_down_temp = time_down_max;
		}
		time_down_max = 1;
		if (time_down > time_down_max) {
			time_down = 1;
		}
	}
	else {
		switch (score / 1000) {
		case 0:
			time_down_temp = 50;
			break;
		case 1:
			time_down_temp = 45;
			break;
		case 2:
			time_down_temp = 40;
			break;
		case 3:
			time_down_temp = 35;
			break;
		case 4:
			time_down_temp = 30;
			time_max = 3;
			break;
		case 5:
			time_down_temp = 25;
			break;
		case 6:
			time_down_temp = 20;
			time_max = 2;
			break;
		}
		time_down_max = time_down_temp;
	}
	if (time_down-- == 0) {
		if (!TetrisManger.MoveDown()) {
			TetrisManger.FixBricks();
			int temp = TetrisManger.RowCheck();
			score = score + (temp * temp) * Singlescore * (1 + (double)score / 10000);
			if (temp != 0) {
				LOG_DEBUG("Score: %d", score);
			}
			TetrisManger.NewRound();
			DrawNext();
		}
		time_down = time_down_max;
	}
	DrawMap(TetrisManger.centre.x, TetrisManger.centre.y, TetrisManger.brickType, TetrisManger.brickState, TetrisManger.bcgSquare);
	return TetrisManger.TopCheck();
}