// TetrisDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Tetris.h"
#include "TetrisDlg.h"
#include "afxdialogex.h"

#include "CGameDlg.h"
#include "Log.h"
#include "GameSDL.h"
#include "CGlobe.h"
#include "CRankList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

// CTetrisDlg 对话框

CTetrisDlg::CTetrisDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TETRIS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTetrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START_BUTTON, _Start_Button);
	DDX_Control(pDX, IDC_RANK_BUTTON, _Rank_Button);
	DDX_Control(pDX, IDC_QUIT_BUTTON, _Quit_Button);
}

BEGIN_MESSAGE_MAP(CTetrisDlg, CDialogEx)
	//	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HELPINFO()
	ON_STN_CLICKED(IDC_START_BUTTON, &CTetrisDlg::OnStnClickedStartButton)
	ON_STN_CLICKED(IDC_RANK_BUTTON, &CTetrisDlg::OnStnClickedRankButton)
	ON_STN_CLICKED(IDC_QUIT_BUTTON, &CTetrisDlg::OnStnClickedExitButton)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CTetrisDlg 消息处理程序

BOOL CTetrisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	Globe.dlg = this;

	GameSDL::StartBKMusic();

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTetrisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect   rect;
		CPaintDC   dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect, RGB(40, 44, 52));
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTetrisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CTetrisDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return true;
}

void CTetrisDlg::OnStnClickedStartButton()
{
	GameSDL::ButtonDownSound();
	CGameDlg dlg;
	this->ShowWindow(SW_HIDE);
	dlg.DoModal();
}

void CTetrisDlg::OnStnClickedRankButton()
{
	GameSDL::ButtonDownSound();
	CRankList dlg;
	dlg.DoModal();
}

void CTetrisDlg::OnStnClickedExitButton()
{
	GameSDL::ButtonDownSound();
	this->OnOK();
}

HBRUSH CTetrisDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}

void CTetrisDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	GameSDL::EndBKMusic();
	CDialogEx::OnOK();
}

BOOL CTetrisDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) {
			return TRUE;
		}
		if (pMsg->wParam == VK_ESCAPE) {
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}