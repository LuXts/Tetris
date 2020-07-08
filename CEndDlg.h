#pragma once

#include "CStaticEX.h"
// CEndDlg 对话框

class CEndDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEndDlg)

private:
	int _Score;
	CFont _font;
public:
	CEndDlg(int Score, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEndDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_END_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CStatic _OverStatic;
	//	CStatic _End_Score;
public:
	afx_msg void OnStnClickedRankButton();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	CString _EndScoreStatic;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStaticEX _Rank_Button;
};
