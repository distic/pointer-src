#include "IWin32_Button.h"

IWin32_Button::IWin32_Button(HWND window, DWORD resId) : IWin32Object(GetDlgItem(window, resId), resId)
{
	// do nothing.
}

IWin32_Button::~IWin32_Button()
{
	DestroyWindow(m_hWnd);
}

void
IWin32_Button::setFont(int size, const char* fontName)
{
	HFONT hFont = CreateFont(size, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, fontName);
	SendMessage(m_hWnd, WM_SETFONT, WPARAM(hFont), TRUE);
}

void
IWin32_Button::setText(const char* text)
{
	SetWindowText(m_hWnd, text);
}

void
IWin32_Button::setEnabled(bool enabled)
{
	EnableWindow(m_hWnd, enabled);
}

void
IWin32_Button::show()
{
	ShowWindow(m_hWnd, SW_SHOW);
}

void
IWin32_Button::hide()
{
	ShowWindow(m_hWnd, SW_HIDE);
}

void
IWin32_Button::setSize(int width, int height)
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	MoveWindow(m_hWnd, rc.left, rc.top, width, height, TRUE);
}

void
IWin32_Button::setLocation(int x, int y)
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	MoveWindow(m_hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, TRUE);
}