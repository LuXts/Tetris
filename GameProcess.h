#pragma once
#include <WinSock2.h>
#include"GameManager.h"
class GameProcess {
public:
	GameManager TetrisManger;

	BOOL TranslateMessage(MSG* pMSG);
	void OnBnClickBegin();
	UINT BeginGame(LPVOID param);
};
