#pragma once

#include "GameSDL.h"
#include "GameProcess.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	//	afx_msg void OnBnClickedButton1();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	// 游戏主要显示区域
	CStatic GameArea;
	// 下一个方块显示区域
	CStatic NextArea;
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	//	afx_msg void OnKillFocus(CWnd* pNewWnd);
private:
	bool _Pause;
	bool _Exit;
	GameSDL* _Game;
	GameProcess* _GProcess;
	CString _Diff;
	CString _Score;
};
