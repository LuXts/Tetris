#include "GameProcess.h"
#include "GameManager.h"
#include <afxwin.h>

/*һ���̣߳����ڽ��ռ�����Ϣ��������ط������*/
BOOL GameProcess::TranslateMessage(MSG* pMSG) {
	if (pMSG->message==WM_KEYDOWN) {
		switch (pMSG->wParam) 
		{
		case VK_UP:
			if (TetrisManger.RotateTop()) {
				/*��ʱΪ����һ�ε�ͼ*/
				break;
			}
		case VK_DOWN:
			if (TetrisManger.MoveDown()) {
				/*��ʱΪ����һ�ε�ͼ*/
				break;
			}
		case VK_LEFT:
			if (TetrisManger.MoveLeft()) {
				/*��ʱΪ����һ�ε�ͼ*/
				break;
			}
		case VK_RIGHT:
			if (TetrisManger.MoveRight()) {
				/*��ʱΪ����һ�ε�ͼ*/
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
		ptask->TetrisManger.NewRound();//�������һ�����飻
		/*�˴�Ϊ�����ұ���ʾ������һ�����顱*/
		/*�˴�Ϊ���ƴ�ʱ�ĵ�ͼ�������������Ļ�ϣ�*/
		Sleep(500);
		while (/*����Ƿ񵽴�׶�*/) {
			ptask->TetrisManger.MoveDown();//�����ƶ�һ��
			/*�˴�Ϊ���ƴ�ʱ�ĵ�ͼ*/
			Sleep(500);
		}
		if (/*����Ƿ񵽴�׶�*/) {
			ptask->TetrisManger.FixBricks();//������д���ͼ
			ptask->TetrisManger.RowCheck();//����Ƿ������ȥ
		}
		if (/*����Ƿ񵽴ﶥ��*/){
			return 0;
		}
	}
	return 0;
}
void GameProcess::OnBnClickBegin() {
	CWinThread* AfxBeginThread( GameProcess::BeginGame,(LPVOID)this);
}