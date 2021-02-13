#include "IWin32_ListView.h"
#include <Uxtheme.h>

#pragma comment (lib, "UxTheme.lib")

IWin32_ListView::IWin32_ListView(HWND hwnd, DWORD resId) : IWin32Object(GetDlgItem(hwnd, resId), resId)
{
	// do nothing.
}

IWin32_ListView::~IWin32_ListView()
{
	// do nothing.
}

void
IWin32_ListView::setFullRowSelect()
{
	ListView_SetExtendedListViewStyle(m_hWnd, LVS_EX_FULLROWSELECT);

	/*SendMessage(m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);*/
}

void 
IWin32_ListView::addItem(IWin32_ListViewItem& lvItem)
{
	SendMessage(m_hWnd, LVM_INSERTITEM, 0, (LPARAM)&lvItem.getHandle());
}

void 
IWin32_ListView::setSize(int width, int height)
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	MoveWindow(m_hWnd, rc.left, rc.top, width, height, TRUE);
}

void 
IWin32_ListView::setLocation(int x, int y)
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	MoveWindow(m_hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, TRUE);
}