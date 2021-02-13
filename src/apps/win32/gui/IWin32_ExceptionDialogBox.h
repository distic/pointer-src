#pragma once

#include "IWin32_Window.h"
#include <functional>

#define IExceptionDialogBox IWin32_ExceptionDialogBox

class IWin32_ExceptionDialogBox {
public:
	static INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	static int showDialog(EXCEPTION_POINTERS* ep);
	static void finishCatch();
	static void addOnStopEvent(std::function<void()> f);

private:
	static const char* getExceptionCodeString(DWORD nativeExceptionCode);
};