#include "IWin32_Window.h"
#include <shellapi.h>
#include <strsafe.h>
#include <algorithm>

static std::vector<IWindow *> m_windows;

IWin32_Window::IWin32_Window(DWORD resourceId) : IWin32Object(nullptr, resourceId)
{
	// do nothing
}

IWin32_Window::~IWin32_Window()
{
	// do nothing.
}

std::vector<IWindow *> IWin32_Window::getAllWindows()
{
	return m_windows;
}

void IWin32_Window::setTitleBarIcon(DWORD resId)
{
	HICON hIcon = (HICON)LoadImage(
		GetModuleHandle(0),
		MAKEINTRESOURCE(resId),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		0);

	if (hIcon)
	{
		SendMessage(m_hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	}
}

void IWin32_Window::setTitle(const char *title)
{
	SetWindowText(m_hWnd, title);
}

void IWin32_Window::setNotifyIcon(INotifyIcon *ni)
{
	m_notifyIcon = ni;
}

bool IWin32_Window::isVisibe()
{
	return IsWindowVisible(getHandle());
}

void IWin32_Window::show()
{
	ShowWindow(m_hWnd, SW_SHOW);
}

void IWin32_Window::hide()
{
	ShowWindow(m_hWnd, SW_HIDE);
}

void IWin32_Window::showDialog(HWND hWndParent)
{
	if (hWndParent == NULL)
	{
		if (!(m_hWnd = CreateDialog(GetModuleHandle(0), MAKEINTRESOURCE(m_resourceId), hWndParent, IWin32_Window::WndProc)))
		{
			throw "Unable to create Win32 Window!";
		}

		m_windows.push_back(this);

		SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
		SendMessageW(m_hWnd, WM_INITDIALOG, 0, 0);

		ShowWindow(m_hWnd, SW_SHOW);
		UpdateWindow(m_hWnd);
	}
	else
	{
		DialogBoxParam(GetModuleHandle(0), MAKEINTRESOURCE(m_resourceId), hWndParent, IWin32_Window::DlgProc, (LPARAM)this);
	}
}

void IWin32_Window::close()
{
	m_windows.erase(std::remove(m_windows.begin(), m_windows.end(), this), m_windows.end());

	SendMessage(m_hWnd, WM_DESTROY, 0, 0);
}

void IWin32_Window::setSize(int width, int height)
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	MoveWindow(m_hWnd, rc.left, rc.top, width, height, TRUE);
}

void IWin32_Window::setLocation(int x, int y)
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	MoveWindow(m_hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, TRUE);
}

UINT WM_TASKBARCREATED = 0;

INT_PTR
IWin32_Window::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	IWin32_Window *self = CLASS_DATA(IWin32_Window, hWnd);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		if (self != nullptr)
		{
			self->m_hWnd = hWnd;
			self->onCreateWindow();
		}
		else
		{
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)lParam);
			SendMessageW(hWnd, WM_INITDIALOG, 0, 0);
		}
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		int wmId = LOWORD(wParam);

		if (wmId == IDOK || wmId == IDCANCEL)
		{
			EndDialog(hWnd, wmId);
			return (INT_PTR)TRUE;
		}
		else
		{
			self->m_collection.at(wmId)();
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR
IWin32_Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	IWin32_Window *self = CLASS_DATA(IWin32_Window, hWnd);

	switch (message)
	{
	case WM_INITDIALOG:
	{
		WM_TASKBARCREATED = RegisterWindowMessage(TEXT("TaskbarCreated"));

		if (self != nullptr)
		{
			self->onCreateWindow();
		}
		break;
	}

	case WMAPP_NOTIFYCALLBACK:
	{
		switch (LOWORD(lParam))
		{

		case NIN_BALLOONTIMEOUT:
			self->m_notifyIcon->RestoreTooltip();
			break;

		case NIN_BALLOONUSERCLICK:
			self->m_notifyIcon->RestoreTooltip();
			// placeholder for the user clicking on the balloon.
			MessageBox(self->getHandle(), "The user clicked on the balloon.", "User click", MB_OK);
			break;

		case WM_LBUTTONUP:
			self->onNotifyIconPrimaryClick();
			break;
		case WM_RBUTTONUP:
			self->onNotifyIconSecondaryClick();
			break;
		}

		return 0;
	}

	case WM_PAINT:
	{
		self->onPaint();
	}

	case WM_CTLCOLORSTATIC:
	{
		return self->onCtlColorStatic(wParam);
	}

	case WM_NOTIFY:
	{
		if (lParam == NULL)
		{ // HACK: or not...
			break;
		}

		switch (((LPNMHDR)lParam)->code)
		{
		case TCN_SELCHANGE:
			self->m_tabSelFn();
			break;
		}
		break;
	}

	case WM_DPICHANGED:
	{
		break;
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		auto fn = self->m_collection.find(wmId);

		if (fn != self->m_collection.end())
		{
			fn->second();
		}

		// auto fn = self->m_collection.at(wmId);

		break;
	}

	case WM_CLOSE:
		SendMessage(hWnd, WM_DESTROY, 0, 0);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
	{
		if (message == WM_TASKBARCREATED)
		{
			self->onCreateWindow();
		}
		break;
	}
	}

	return (INT_PTR)FALSE;
}