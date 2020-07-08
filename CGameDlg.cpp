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

#include "CPauseDlg.h"
#include "CEndDlg.h"

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent), _Game(NULL)
	, _Diff(_T(""))
	, _Score(_T(""))
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
	DDX_Text(pDX, IDC_DIFF_TEXT, _Diff);
	DDX_Text(pDX, IDC_SCORE_TEXT, _Score);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	//	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_WM_HELPINFO()
	//	ON_WM_KEYDOWN()
	//	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_PAINT()
	//	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

// CGameDlg 消息处理程序

BOOL CGameDlg::DestroyWindow()
{
	Globe.KEY_UP = FALSE;
	Globe.KEY_DOWN = FALSE;
	Globe.KEY_LEFT = FALSE;
	Globe.KEY_RIGHT = FALSE;
	Globe.KEY_PAUSE = FALSE;

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
	_GProcess->DrawNext();
	SetTimer(17, 10, NULL);

	_Pause = false;
	_Exit = false;
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

HBRUSH CGameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_GAME_WINDOW) {
		_Game->MainRendererPresent();
	}
	else if (pWnd->GetDlgCtrlID() == IDC_NEXT_BRICK_PIC) {
		_Game->NextRendererPresent();
	}
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC: //对所有静态文本框的设置
	{
		pDC->SetBkMode(TRANSPARENT);
		//设置背景为透明
		pDC->SetTextColor(RGB(200, 200, 200)); //设置字体颜色
		HBRUSH B = CreateSolidBrush(RGB(46, 50, 58));
		//创建画刷
		return (HBRUSH)B; //返回画刷句柄
	}
	}
	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

BOOL CGameDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
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
		if (pMsg->wParam == VK_ESCAPE) {
			KillTimer(17);
			_Pause = true;
			CPauseDlg Dlg(_GProcess->score, &_Exit);
			Dlg.DoModal();
			if (_Exit) {
				this->OnOK();
			}
			_Pause = false;
			SetTimer(17, 10, NULL);
			return TRUE;
		}
	}

	if (pMsg->message == WM_KEYUP) {
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
		_Score.Format(_T("%d"), _GProcess->score);
		_Diff.Format(_T("%d"), _GProcess->score / 1000 + 1);

		UpdateData(FALSE);
		if (_GProcess->Around()) {
			KillTimer(17);
			CEndDlg dlg(_GProcess->score);
			dlg.DoModal();
			this->OnOK();
		}
		return;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::OnPaint()
{
	CRect   rect;
	CPaintDC   dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(46, 50, 58));
}