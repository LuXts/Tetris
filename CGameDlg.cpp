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
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
END_MESSAGE_MAP()

// CGameDlg 消息处理程序

BOOL CGameDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	LOG(lena::LOG_LEVEL_DEBUG, "GameDlg Destroy!");
	printf("GameDlg Destroy!");
	return CDialogEx::DestroyWindow();
}