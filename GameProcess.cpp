#include "GameProcess.h"
#include "GameManager.h"
#include <afxwin.h>

/*一个线程：用于接收键盘消息并进行相关方块操作*/
BOOL GameProcess::TranslateMessage(MSG* pMSG) {
	if (pMSG->message==WM_KEYDOWN) {
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
}
UINT GameProcess::BeginGame(LPVOID param) {
	GameProcess* ptask = (GameProcess*)param;
	while (1) {
		ptask->TetrisManger.NewRound();//随机产生一个方块；
		/*此处为绘制右边提示栏“下一个方块”*/
		/*此处为绘制此时的地图（方块出现在屏幕上）*/
		Sleep(500);
		while (/*检测是否到达底端*/) {
			ptask->TetrisManger.MoveDown();//向下移动一格
			/*此处为绘制此时的地图*/
			Sleep(500);
		}
		if (/*检测是否到达底端*/) {
			ptask->TetrisManger.FixBricks();//将方块写入地图
			ptask->TetrisManger.RowCheck();//检测是否成行消去
		}
		if (/*检测是否到达顶部*/){
			return 0;
		}
	}
	return 0;
}
void GameProcess::OnBnClickBegin() {
	CWinThread* AfxBeginThread( GameProcess::BeginGame,(LPVOID)this);
}