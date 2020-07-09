// TetrisDlg.h: 头文件
//

#pragma once

#include "CStaticEX.h"

// CTetrisDlg 对话框
class CTetrisDlg : public CDialogEx
{
	// 构造
public:
	CTetrisDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TETRIS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnStnClickedStartButton();
	afx_msg void OnStnClickedRankButton();
	afx_msg void OnStnClickedExitButton();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	CStaticEX _Start_Button;
	CStaticEX _Rank_Button;
	CStaticEX _Quit_Button;
	virtual void OnOK();
};
