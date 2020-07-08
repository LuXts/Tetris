#pragma once

// CStaticEX

class CStaticEX : public CStatic
{
	DECLARE_DYNAMIC(CStaticEX)

public:
	CStaticEX();
	virtual ~CStaticEX();

protected:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

private:
	COLORREF m_clrHoverTextColor;
	COLORREF m_clrCurTextColor;
	HBRUSH m_brBkgndHover;
	HBRUSH m_brBkgndDefault;
	bool m_bMouseTrack;
public:
	void SetTextHoverColor(COLORREF clr);
	void SetBackHoverColor(COLORREF clr);
};
