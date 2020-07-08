// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "Tetris.h"
#include "CGameDlg.h"
#include "afxdialogex.h"

#include "Log.h"
#include"GameProcess.h"
#include"GameManager.h"
#include "CGlobe.h"

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent), _Game(NULL)
{
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_WINDOW, GameArea);
	DDX_Control(pDX, IDC_NEXT_BRICK_PIC, NextArea);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedButton1)
	//	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_WM_HELPINFO()
	//	ON_WM_KEYDOWN()
	//	ON_WM_KEYUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CGameDlg 消息处理程序

BOOL CGameDlg::DestroyWindow()
{
	KillTimer(17);
	// TODO: 在此添加专用代码和/或调用基类
	delete _Game;
	delete _GProcess;
	LOG(lena::LOG_LEVEL_DEBUG, "GameDlg Destroy!");
	return CDialogEx::DestroyWindow();
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HICON m_hIcon = AfxGetApp()->LoadIconW(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);

	GameArea.SetWindowPos(NULL, 0, 0, 300, 600, SWP_NOMOVE);
	NextArea.SetWindowPos(NULL, 0, 0, 120, 120, SWP_NOMOVE);
	CRect rect, rectClient;
	GetWindowRect(rect);
	GetClientRect(rectClient);
	//LOG(lena::LOG_LEVEL_DEBUG, "Height: %d", GetSystemMetrics(SM_CYSIZE));
	SetWindowPos(NULL, 0, 0, 465, rect.Height() - rectClient.Height() + 600, SWP_NOMOVE);

	_Game = new GameSDL(GameArea.GetSafeHwnd(), NextArea.GetSafeHwnd());
	_GProcess = new GameProcess(_Game);

	_GProcess->TetrisManger.NewGame();

	SetTimer(17, 10, NULL);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CGameDlg::OnBnClickedButton1()
{
	/*static int x = 0, y = 0;

	_Game->MainRendererClear();

	_Game->MainAddBrick(x, y);
	_Game->MainAddBrick(x + 1, y);
	_Game->MainAddBrick(x, y + 1);
	_Game->MainAddBrick(x + 1, y + 1);

	_Game->MainRendererPresent();

	_Game->NextRendererClear();
	_Game->NextAddBrick(x % 4, y % 4);
	_Game->NextRendererPresent();

	x++;
	y++;
	x = x % 10;
	y = y % 10;*/

	// TODO: 在此添加控件通知处理程序代码
	/*
	GameProcess A(_Game);
	A.TetrisManger.NewGame();
	A.TetrisManger.NewRound();
	A.InitBrick();
	for (int i = 0; i < 5; i++) {
		A.TetrisManger.MoveDown();
	}
	A.TetrisManger.FixBricks();
	A.TetrisManger.NewRound();
	A.InitBrick();
	A.DrawMap(A.TetrisManger.centre.x, (A.TetrisManger.centre.y + 3), A.TetrisManger.brickType, A.TetrisManger.brickState, A.TetrisManger.bcgSquare);
	*/
}

HBRUSH CGameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	_Game->MainRendererPresent();
	_Game->NextRendererPresent();
	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

BOOL CGameDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return true;
}

BOOL CGameDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_UP)
		{
			Globe.KEY_UP = TRUE;
			return TRUE;
		}
		if (pMsg->wParam == VK_DOWN)
		{
			Globe.KEY_DOWN = TRUE;
			return TRUE;
		}
		if (pMsg->wParam == VK_LEFT)
		{
			Globe.KEY_LEFT = TRUE;
			return TRUE;
		}
		if (pMsg->wParam == VK_RIGHT)
		{
			Globe.KEY_RIGHT = TRUE;
			return TRUE;
		}
	}

	if (pMsg->message == WM_KEYUP) {
		/*
		if (pMsg->wParam == VK_UP)
		{
			Globe.KEY_UP = FALSE;
			return TRUE;
		}
		if (pMsg->wParam == VK_LEFT)
		{
			Globe.KEY_LEFT = FALSE;
			return TRUE;
		}
		if (pMsg->wParam == VK_RIGHT)
		{
			Globe.KEY_RIGHT = FALSE;
			return TRUE;
		}
		*/
		if (pMsg->wParam == VK_DOWN)
		{
			Globe.KEY_DOWN = FALSE;
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 17) {
		_GProcess->Around();
	}
	CDialogEx::OnTimer(nIDEvent);
}