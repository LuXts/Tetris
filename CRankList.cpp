// CRankList.cpp: 实现文件
//

#include "pch.h"
#include "Tetris.h"
#include "CRankList.h"
#include "afxdialogex.h"

#include "CGlobe.h"
#include "CJson.h"
#include "Log.h"

// CRankList 对话框

IMPLEMENT_DYNAMIC(CRankList, CDialogEx)

CRankList::CRankList(CWnd* pParent /*=nullptr*/, int score)
	: CDialogEx(IDD_RANK_DIALOG, pParent), _Score(score)
	, _ScoreText(_T(""))
{
}

CRankList::~CRankList()
{
}

void CRankList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RANK_STATIC, _RankStatic);
	DDX_Control(pDX, IDC_SCORE_STATIC, _ScoreStatic);
	DDX_Text(pDX, IDC_SCORE_STATIC, _ScoreText);
	DDX_Control(pDX, IDC_INDEX_LIST, _Index_ListBox);
	DDX_Control(pDX, IDC_NAME_LIST, _Name_ListBox);
	DDX_Control(pDX, IDC_SCORE_LIST, _Score_ListBox);
	DDX_Control(pDX, IDC_EXIT_MAIN, _Exit_Main);
}

BOOL CRankList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	_font.CreatePointFont(180, _T("Microsoft Sans Serif"));
	_RankStatic.SetFont(&_font);

	CJson::load(_NameList, _ScoreList);

	LPWSTR szBuffer;
	szBuffer = (LPWSTR)malloc(500);
	DWORD dwNameLe = 500;
	if (!GetUserName(szBuffer, &dwNameLe)) {
		LOG(lena::LOG_LEVEL_ERROR, "GetUserName Error %d", GetLastError());
	}
	else {
		_Name += szBuffer;
	}
	if (szBuffer) {
		free(szBuffer);
	}
	_Name = _T("老王测试员");

	if (_Score > 0) {
		if (_ScoreList.size() == 0) {
			_ScoreList.emplace_back(_Score);
			_NameList.emplace_back(_Name);
		}
		else {
			int total = _ScoreList.size();
			int i = 0;
			for (; i < total; i++) {
				if (_ScoreList[i] < _Score) {
					_ScoreList.insert(_ScoreList.begin() + i, _Score);
					_NameList.insert(_NameList.begin() + i, _Name);
					break;
				}
			}
			if (i == total) {
				_ScoreList.emplace_back(_Score);
				_NameList.emplace_back(_Name);
			}
			while (_ScoreList.size() > 10) {
				_ScoreList.pop_back();
				_NameList.pop_back();
			}
		}
	}

	int total = _ScoreList.size();

	for (int i = 0; i < total; i++) {
		CString index;
		CString CScore;
		index.Format(_T("%d"), i + 1);
		CScore.Format(_T("%d"), _ScoreList[i]);
		_Index_ListBox.AddString(index);
		_Name_ListBox.AddString(_NameList[i]);
		_Score_ListBox.AddString(CScore);
	}

	if (_Score < 0) {
		_ScoreStatic.ShowWindow(SW_HIDE);
	}
	else {
		_ScoreStatic.ShowWindow(SW_SHOWNORMAL);
		_ScoreText.Format(_T("本局分数为：   %d"), _Score);
		UpdateData(FALSE);
	}

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

BEGIN_MESSAGE_MAP(CRankList, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_HELPINFO()
	ON_STN_CLICKED(IDC_EXIT_MAIN, &CRankList::OnStnClickedExitMain)
END_MESSAGE_MAP()

// CRankList 消息处理程序

void CRankList::OnPaint()
{
	CRect   rect;
	CPaintDC   dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(53, 57, 65));
}

HBRUSH CRankList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	auto i = pWnd->GetDlgCtrlID();
	if (i == IDC_T1_STATIC || i == IDC_T2_STATIC || i == IDC_T3_STATIC) {
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(200, 200, 200));
		HBRUSH B = CreateSolidBrush(RGB(62, 66, 73));
		return (HBRUSH)B;
	}
	else if (i == IDC_RANK_STATIC || i == IDC_SCORE_STATIC) {
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(230, 230, 230));
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	switch (nCtlColor)
	{
	case CTLCOLOR_LISTBOX:
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(200, 200, 200));
		HBRUSH B = CreateSolidBrush(RGB(62, 66, 73));
		return (HBRUSH)B;
	}
	}
	return hbr;
}

BOOL CRankList::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE) {
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CRankList::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return TRUE;
}

void CRankList::OnStnClickedExitMain()
{
	this->OnOK();
	if (Globe.dlg != NULL) {
		Globe.dlg->ShowWindow(SW_SHOWNORMAL);
	}
	// TODO: 在此添加控件通知处理程序代码
}

BOOL CRankList::DestroyWindow()
{
	CJson::save(_NameList, _ScoreList);
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::DestroyWindow();
}