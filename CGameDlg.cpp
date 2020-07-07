// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "Tetris.h"
#include "CGameDlg.h"
#include "afxdialogex.h"

#include "Log.h"

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
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedButton1)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CGameDlg 消息处理程序

BOOL CGameDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	delete _Game;
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
	CRect rect;
	GetWindowRect(rect);
	MoveWindow(rect.left, rect.top, rect.Width(), rect.Height() - 50);

	_Game = new GameSDL(GetDlgItem(IDC_GAME_WINDOW)->GetSafeHwnd());
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CGameDlg::OnBnClickedButton1()
{
	static int x = 0, y = 0;

	_Game->RendererClear();

	_Game->MapAddBrick(x, y);
	_Game->MapAddBrick(x + 2, y);
	_Game->MapAddBrick(x, y + 2);

	_Game->RendererPresent();

	x++;
	y++;
	x = x % 10;
	y = y % 10;
	// TODO: 在此添加控件通知处理程序代码
}

//BOOL CGameDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
//{
//	_Game->RendererClear();
//	// TODO: 在此添加专用代码和/或调用基类
//	_Game->RendererPresent();
//	return CDialogEx::Create(lpszTemplateName, pParentWnd);
//}

void CGameDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	//_Game->RendererPresent();
	// TODO: 在此处添加消息处理程序代码
}

HBRUSH CGameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	_Game->RendererPresent();
	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}