#include "IWin32_CheckBox.h"

IWin32_CheckBox::IWin32_CheckBox(HWND window, DWORD resId) : IWin32Object(GetDlgItem(window, resId), resId)
{
	// do nothing.
}

IWin32_CheckBox::~IWin32_CheckBox()
{
	DestroyWindow(m_hWnd);
}

void
IWin32_CheckBox::setFont(int size, const char* fontName)
{
	HFONT hFont = CreateFont(size, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, fontName);
	SendMessage(m_hWnd, WM_SETFONT, WPARAM(hFont), TRUE);
}

void
IWin32_CheckBox::setText(const char* text)
{
	SetWindowText(m_hWnd, text);
}

void
IWin32_CheckBox::setEnabled(bool enabled)
{
	EnableWindow(m_hWnd, enabled);
}

void
IWin32_CheckBox::show()
{
	ShowWindow(m_hWnd, SW_SHOW);
}

void
IWin32_CheckBox::hide()
{
	ShowWindow(m_hWnd, SW_HIDE);
}

void IWin32_CheckBox::setSize(int width, int height)
{
}

void IWin32_CheckBox::setLocation(int x, int y)
{
}

void
IWin32_CheckBox::setChecked()
{

}

void 
IWin32_CheckBox::setUnchecked()
{

}

bool 
IWin32_CheckBox::isChecked()
{
	return true;
}