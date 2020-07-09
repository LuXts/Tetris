#pragma once

#include "CStaticEX.h"
// CPauseDlg 对话框

class CPauseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPauseDlg)

public:
	CPauseDlg(int score, bool* exit, CWnd* pParent = nullptr);
	virtual ~CPauseDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAUSE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBackButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedBackStatic();
	afx_msg void OnStnClickedExitStatic();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
private:
	bool* _Exit;
	int _Score;
	CFont _font;
	CStatic _OverGame;
	CStaticEX _Back_Button;
	CStaticEX _Exit_Button;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
