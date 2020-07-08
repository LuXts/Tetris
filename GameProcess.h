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
	int n;//�����ж��Ƿ��Զ����䣻
	int x=1;//�жϵ�ǰ����Ϸ״̬��1��ʾ�������䣬2��ʾ���ף�3��ʾ�ڶ��ˣ�

	GameProcess(GameSDL* A) {
		GameDraw = A;
	}
	BOOL TranslateMessage(MSG* pMSG);
	void OnBnClickBegin();
	UINT BeginGame(LPVOID param);
	void DrawMap(int x, int y, int type, int state, SingleSquare bcgSquare[WidthBySquare][HeightBySquare + 4]);
	//BOOL BeginGame();
	BOOL Around();//һ���������Ϸ����
	BOOL InitBrick();//�������ƶ������϶ˣ�
};
