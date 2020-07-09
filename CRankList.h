#pragma once

#include <vector>
#include "CStaticEX.h"

// CRankList 对话框

class CRankList : public CDialogEx
{
	DECLARE_DYNAMIC(CRankList)

public:
	CRankList(CWnd* pParent = nullptr, int score = -1);
	virtual ~CRankList();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RANK_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnStnClickedExitMain();
	virtual BOOL DestroyWindow();
	afx_msg void OnNMCustomdrawRankList(NMHDR* pNMHDR, LRESULT* pResult);
private:
	int _Score;
	CFont _font;
	CString _Name;
	std::vector<int> _ScoreList;
	std::vector<CString> _NameList;
	CStatic _RankStatic;
	CString _ScoreText;
	CStatic _ScoreStatic;
	CListBox _Index_ListBox;
	CListBox _Name_ListBox;
	CListBox _Score_ListBox;
	CStaticEX _Exit_Main;
};
