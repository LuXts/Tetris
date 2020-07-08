#pragma once

#include <vector>
#include "CStaticEX.h"

// CRankList 对话框

class CRankList : public CDialogEx
{
	DECLARE_DYNAMIC(CRankList)
private:
	int _Score;
	CFont _font;
	CString _Name;
	std::vector<int> _ScoreList;
	std::vector<CString> _NameList;

public:
	CRankList(CWnd* pParent = nullptr, int score = -1);   // 标准构造函数
	virtual ~CRankList();

	// 对话框数据
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
private:
	CStatic _RankStatic;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnStnClickedExitMain();
private:
	CStatic _ScoreStatic;
public:
	CString _ScoreText;
	virtual BOOL DestroyWindow();
public:
	//	afx_msg void OnNMCustomdrawRankList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawRankList(NMHDR* pNMHDR, LRESULT* pResult);
private:
	CListBox _Index_ListBox;
public:
	CListBox _Name_ListBox;
	CListBox _Score_ListBox;
private:
	CStaticEX _Exit_Main;
};
