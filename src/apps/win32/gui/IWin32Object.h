#pragma once

#include "misc/framework.h"

class IWin32Object
{

public:
	IWin32Object(HWND hwnd, DWORD resourceId = -1) : m_resourceId(resourceId),
													 m_hWnd(hwnd)
	{
		//
		// Article from MSDN:
		// https://docs.microsoft.com/en-us/windows/win32/directwrite/how-to-ensure-that-your-application-displays-properly-on-high-dpi-displays#gdi
		//

		// TODO: We need a way to detect DPI change during runtime and have these values update.
		HDC screen = GetDC(0);
		dpiX = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSX));
		dpiY = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSY));
		ReleaseDC(0, screen);
	}

	virtual void onFatalErrorRaised() {
		/* do nothing */
	}

public:
	HWND getHandle()
	{
		return m_hWnd;
	}

	DWORD getResourceId()
	{
		return m_resourceId;
	}

protected:
	HWND m_hWnd;
	DWORD m_resourceId;

	//
	// Article from MSDN:
	// https://docs.microsoft.com/en-us/windows/win32/directwrite/how-to-ensure-that-your-application-displays-properly-on-high-dpi-displays#gdi
	//
	FLOAT dpiX, dpiY;
};