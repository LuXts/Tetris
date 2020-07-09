// CEndDlg.cpp: 实现文件
//

#include "pch.h"
#include "Tetris.h"
#include "CEndDlg.h"
#include "afxdialogex.h"

#include "GameSDL.h"
#include "CRankList.h"
// CEndDlg 对话框

IMPLEMENT_DYNAMIC(CEndDlg, CDialogEx)

CEndDlg::CEndDlg(int Score, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_END_DIALOG, pParent)
	, _EndScoreStatic(_T(""))
	, _Score(Score)
{
}

CEndDlg::~CEndDlg()
{
}

void CEndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OVER_STATIC, _OverStatic);
	//  DDX_Control(pDX, IDC_END_SCORE_STATIC, _End_Score);
	DDX_Text(pDX, IDC_END_SCORE_STATIC, _EndScoreStatic);
	DDX_Control(pDX, IDC_RANK_BUTTON, _Rank_Button);
}

BEGIN_MESSAGE_MAP(CEndDlg, CDialogEx)
	ON_STN_CLICKED(IDC_RANK_BUTTON, &CEndDlg::OnStnClickedRankButton)
	ON_WM_PAINT()
	ON_WM_HELPINFO()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CEndDlg 消息处理程序

void CEndDlg::OnStnClickedRankButton()
{
	GameSDL::ButtonDownSound();
	CRankList dlg(nullptr, _Score);
	this->OnOK();
	dlg.DoModal();
}

void CEndDlg::OnPaint()
{
	CRect   rect;
	CPaintDC   dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(53, 57, 65));
}

BOOL CEndDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	_font.CreatePointFont(180, _T("Microsoft Sans Serif"));
	_OverStatic.SetFont(&_font);

	_EndScoreStatic.Format(_T("本局分数为：   %d"), _Score);
	UpdateData(FALSE);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

BOOL CEndDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}

HBRUSH CEndDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	auto i = pWnd->GetDlgCtrlID();
	if (i == IDC_OVER_STATIC || i == IDC_END_SCORE_STATIC) {
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(230, 230, 230));
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return hbr;
}