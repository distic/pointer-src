#include "IWin32_TabPage.h"

IWin32_TabPage::IWin32_TabPage(HWND parent, DWORD resourceId) : IWin32Object(nullptr, resourceId)
{
	if (!(m_hWnd = CreateDialog(GetModuleHandle(0), MAKEINTRESOURCE(resourceId), parent, IWin32_TabPage::WndProc)))
	{
		throw "Unable to create tab page!";
	}
}

IWin32_TabPage::~IWin32_TabPage()
{
	DestroyWindow(m_hWnd);
}

void
IWin32_TabPage::show()
{
	if (shouldInjectLongPtr()) {
		injectLongPtr();
	}

	ShowWindow(m_hWnd, SW_SHOW);
}

void
IWin32_TabPage::hide()
{
	if (shouldInjectLongPtr()) {
		injectLongPtr();
	}

	ShowWindow(m_hWnd, SW_HIDE);
}

INT_PTR
IWin32_TabPage::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	IWin32_TabPage* self = CLASS_DATA(IWin32_TabPage, hWnd);

	switch (message)
	{
	case WM_INITDIALOG: {
		if (self != nullptr) {
			self->onCreateTabPage();
		}
		break;
	}

	case WM_CTLCOLORSTATIC:
	{
		static HBRUSH hBrushColor;
		if (!hBrushColor)
		{
			hBrushColor = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
			SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
		}
		return (LRESULT)hBrushColor;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		RECT rc;
		HDC hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rc);
		SetDCBrushColor(hdc, GetSysColor(COLOR_WINDOW));
		FillRect(hdc, &rc, (HBRUSH)GetStockObject(DC_BRUSH));

		//or use ps.rcPaint to repaint only the section which requires update
		//FillRect(hdc, &ps.rcPaint, (HBRUSH)GetStockObject(DC_BRUSH));

		EndPaint(hWnd, &ps);
		return 0;
	}

	case WM_DPICHANGED: {

		break;
	}

	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		
		if (self->m_collection.empty())
			break;

		if (self->m_collection.at(wmId) != nullptr)
			self->m_collection.at(wmId)();

		break;
	}

	case WM_DESTROY:

		break;
	}

	return (INT_PTR)FALSE;
}

inline
bool
IWin32_TabPage::shouldInjectLongPtr()
{
	return CLASS_DATA(IWin32_TabPage, m_hWnd) == nullptr;
}

void
IWin32_TabPage::injectLongPtr()
{
	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	SendMessageW(m_hWnd, WM_INITDIALOG, 0, 0);
}