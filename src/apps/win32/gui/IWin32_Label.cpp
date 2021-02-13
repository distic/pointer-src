#include "IWin32_Label.h"

IWin32_Label::IWin32_Label(HWND window, DWORD resId) : IWin32Object(GetDlgItem(window, resId), resId)
{
	// do nothing.
}

IWin32_Label::~IWin32_Label()
{
	DestroyWindow(m_hWnd);
}

void
IWin32_Label::setFont(int size, const char* fontName)
{
	HFONT hFont = CreateFont(size, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, fontName);
	SendMessage(m_hWnd, WM_SETFONT, WPARAM(hFont), TRUE);
}

void 
IWin32_Label::setText(const char* text)
{
	SetWindowText(m_hWnd, text);
}

void 
IWin32_Label::setEnabled(bool enabled)
{
	EnableWindow(m_hWnd, enabled);
}

void
IWin32_Label::show()
{
	ShowWindow(m_hWnd, SW_SHOW);
}

void 
IWin32_Label::hide()
{
	ShowWindow(m_hWnd, SW_HIDE);
}

void
IWin32_Label::setSize(int width, int height)
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	MoveWindow(m_hWnd, rc.left, rc.top, width, height, TRUE);
}

void
IWin32_Label::setLocation(int x, int y)
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	MoveWindow(m_hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, TRUE);
}

int IWin32_Label::getWidth()
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	return rc.right;
}

int IWin32_Label::getHeight()
{
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	return rc.bottom;
}