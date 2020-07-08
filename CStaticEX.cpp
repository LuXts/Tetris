// CStaticEX.cpp: 实现文件
//

#include "pch.h"
#include "Tetris.h"
#include "CStaticEX.h"

// CStaticEX

IMPLEMENT_DYNAMIC(CStaticEX, CStatic)

CStaticEX::CStaticEX()
{
	m_clrCurTextColor = RGB(200, 200, 200);
	m_clrHoverTextColor = RGB(230, 230, 230);
	m_brBkgndDefault = CreateSolidBrush(RGB(62, 66, 73));
	m_brBkgndHover = GetSysColorBrush(COLOR_HIGHLIGHT);
	m_bMouseTrack = true;
}

CStaticEX::~CStaticEX()
{
	DeleteObject(m_brBkgndDefault);
	DeleteObject(m_brBkgndHover);
}

BEGIN_MESSAGE_MAP(CStaticEX, CStatic)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSEHOVER, &OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE, &OnMouseLeave)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

void CStaticEX::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bMouseTrack)
	{
		TRACE("OnMouseMove\n");
		m_bMouseTrack = false;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		//tme.dwHoverTime = HOVER_DEFAULT;
		tme.dwHoverTime = 1;
		tme.hwndTrack = m_hWnd;
		_TrackMouseEvent(&tme);
	}
	CStatic::OnMouseMove(nFlags, point);
}

LRESULT CStaticEX::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_clrCurTextColor = m_clrHoverTextColor;
	Invalidate();
	TRACE("OnMouseHover\n");
	return 0;
}

LRESULT CStaticEX::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_clrCurTextColor = RGB(200, 200, 200);
	m_bMouseTrack = true;
	Invalidate();
	TRACE("OnMouseLeave\n");
	return 0;
}

HBRUSH CStaticEX::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_clrCurTextColor);
	if (m_bMouseTrack)
		return m_brBkgndDefault;
	else
		return m_brBkgndHover;
}

void CStaticEX::SetTextHoverColor(COLORREF clr)
{
	m_clrHoverTextColor = clr;
}

void CStaticEX::SetBackHoverColor(COLORREF clr)
{
	if (m_brBkgndHover)
	{
		DeleteObject(m_brBkgndHover);
	}
	m_brBkgndHover = CreateSolidBrush(clr);
}
