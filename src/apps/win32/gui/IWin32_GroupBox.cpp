#include "IWin32_GroupBox.h"

IWin32_GroupBox::IWin32_GroupBox(HWND window, DWORD resourceId) : IWin32Object(window, resourceId)
{
	// do nothing.
}

IWin32_GroupBox::~IWin32_GroupBox()
{
	// do nothing.
}

void 
IWin32_GroupBox::setTitle(const char* title)
{
	SetDlgItemText(m_hWnd, m_resourceId, title);
}

void 
IWin32_GroupBox::setSize(int width, int height)
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	MoveWindow(m_hWnd, rc.left, rc.top, width, height, TRUE);
}

void 
IWin32_GroupBox::setLocation(int x, int y)
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	MoveWindow(m_hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, TRUE);
}