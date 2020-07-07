﻿#include "pch.h"

#include "GameProcess.h"
#include "GameManager.h"
#include "SingleSquare.h"
#include "Bricks.h"
#include <afxwin.h>
#include "CGlobe.h"


/*一个线程：用于接收键盘消息并进行相关方块操作*/
BOOL GameProcess::TranslateMessage(MSG* pMSG) {
	if (pMSG->message == WM_KEYDOWN) {
		switch (pMSG->wParam)
		{
		case VK_UP:
			if (TetrisManger.RotateTop()) {
				/*此时为绘制一次地图*/
				break;
			}
		case VK_DOWN:
			if (TetrisManger.MoveDown()) {
				/*此时为绘制一次地图*/
				break;
			}
		case VK_LEFT:
			if (TetrisManger.MoveLeft()) {
				/*此时为绘制一次地图*/
				break;
			}
		case VK_RIGHT:
			if (TetrisManger.MoveRight()) {
				/*此时为绘制一次地图*/
				break;
			}
		default:
			break;
		}
	}
	return TRUE;
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
void GameProcess::OnBnClickBegin() {
	//CWinThread* AfxBeginThread(GameProcess::BeginGame, (LPVOID)this);
}
void GameProcess::DrawMap(int x,int y,int type,int state,SingleSquare bcgSquare[WidthBySquare][HeightBySquare + 4]) {
	GameDraw->MainRendererClear();
	GameDraw->MainAddBrick(x + bricks[type][state].p[0].x, y + bricks[type][state].p[0].y);
	GameDraw->MainAddBrick(x+bricks[type][state].p[1].x,y+bricks[type][state].p[1].y);
	GameDraw->MainAddBrick(x + bricks[type][state].p[2].x, y + bricks[type][state].p[2].y);
	GameDraw->MainAddBrick(x + bricks[type][state].p[3].x, y + bricks[type][state].p[3].y);
	for (int i = 0;i < WidthBySquare;i++) {
		for (int j = 0;j < HeightBySquare;j++) {
			if (bcgSquare[i][j].state==1) {
				GameDraw->MainAddBrick(i,j);
			}
		}
	}
	GameDraw->MainRendererPresent();
}
BOOL GameProcess::Around() {
	if (Globe.KEY_UP==TRUE) {
		TetrisManger.RotateTop();
	}
	if (Globe.KEY_LEFT==TRUE) {
		TetrisManger.MoveLeft();
	}
	if (Globe.KEY_RIGHT==TRUE) {
		TetrisManger.MoveRight();
	}
	if (Globe.KEY_DOWN==TRUE) {
		if (!TetrisManger.MoveDown()) {
			TetrisManger.FixBricks();
			score = score + (TetrisManger.RowCheck()* TetrisManger.RowCheck()) * Singlescore;
			if (TetrisManger.TopCheck(TetrisManger.centre, bricks[TetrisManger.brickType][TetrisManger.brickState])) {
				x = 3;
				n = 0;
				DrawMap(-5, -5, 1, 1, TetrisManger.bcgSquare);
				return TRUE;
			}//检测是否到顶端
			x = 2;
			n = 0;
			DrawMap(-5,-5,1,1,TetrisManger.bcgSquare);
			return TRUE;
		}//检测是否到底端
	}
	n=n+1;
	if (n==30) {
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
	}
	x = 1;
	DrawMap(TetrisManger.centre.x,TetrisManger.centre.y,TetrisManger.brickType,TetrisManger.brickState, TetrisManger.bcgSquare);
	return TRUE;
}
BOOL GameProcess::InitBrick() {
	while (1) {
		for (int i = 0;i < 4;i++) {
			if (bricks[TetrisManger.brickState][TetrisManger.brickType].p[i].y == 0) {
				return TRUE;
			}
		}
		TetrisManger.MoveDown();
	}
}//将方块调整到最上面一层



