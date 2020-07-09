// CPauseDlg.cpp: 实现文件
//

#include "pch.h"
#include "Tetris.h"
#include "CPauseDlg.h"
#include "afxdialogex.h"

#include "CRankList.h"
#include "CGlobe.h"

// CPauseDlg 对话框

IMPLEMENT_DYNAMIC(CPauseDlg, CDialogEx)

CPauseDlg::CPauseDlg(int score, bool* exit, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAUSE_DIALOG, pParent), _Score(score), _Exit(exit)
{
}

CPauseDlg::~CPauseDlg()
{
}

void CPauseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PAUSE_STATIC, _OverGame);
	DDX_Control(pDX, IDC_BACK_STATIC, _Back_Button);
	DDX_Control(pDX, IDC_EXIT_STATIC, _Exit_Button);
}

BEGIN_MESSAGE_MAP(CPauseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_BACK_STATIC, &CPauseDlg::OnStnClickedBackStatic)
	ON_STN_CLICKED(IDC_EXIT_STATIC, &CPauseDlg::OnStnClickedExitStatic)
	ON_WM_HELPINFO()
END_MESSAGE_MAP()

// CPauseDlg 消息处理程序

BOOL CPauseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	_font.CreatePointFont(180, _T("Microsoft Sans Serif"));
	_OverGame.SetFont(&_font);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CPauseDlg::OnPaint()
{
	CRect   rect;
	CPaintDC   dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(53, 57, 65));
}

HBRUSH CPauseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	auto i = pWnd->GetDlgCtrlID();
	if (i == IDC_PAUSE_STATIC) {
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(230, 230, 230));
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return hbr;
}

void CPauseDlg::OnStnClickedBackStatic()
{
	GameSDL::ButtonDownSound();
	this->OnOK();
	// TODO: 在此添加控件通知处理程序代码
}

void CPauseDlg::OnStnClickedExitStatic()
{
	GameSDL::ButtonDownSound();
	*_Exit = true;
	if (_Score == 0) {
		if (Globe.dlg != NULL) {
			Globe.dlg->ShowWindow(SW_SHOWNORMAL);
		}
	}
	else {
		CRankList dlg(nullptr, _Score);
		dlg.DoModal();
	}
	this->OnOK();
}

BOOL CPauseDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}

BOOL CPauseDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) {
			OnStnClickedBackStatic();
			return TRUE;
		}
		if (pMsg->wParam == VK_ESCAPE) {
			OnStnClickedBackStatic();
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}