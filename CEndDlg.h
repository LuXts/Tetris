#pragma once

#include "CStaticEX.h"
// CEndDlg 对话框

class CEndDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEndDlg)

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
	int _Score;
	CFont _font;
	CString _EndScoreStatic;
	CStatic _OverStatic;
	CStaticEX _Rank_Button;
public:
	afx_msg void OnStnClickedRankButton();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
