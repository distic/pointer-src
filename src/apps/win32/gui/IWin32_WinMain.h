#pragma once

#include "misc/framework.h"
#include "IWin32_Window.h"
#include <functional>

class IWin32_WinMain {

public:
	IWin32_WinMain(IWindow&);
	virtual ~IWin32_WinMain();

	int runWindowsLooper();
	void registerExtraLoopFunction(std::function<void()> fn);

	IWindow* getMainWindow() const;

private:
	// Forward declarations of functions included in this code module:
	ATOM                myRegisterClass(HINSTANCE hInstance);
	BOOL                initInstance(HINSTANCE, int);
	
	int doRunWindowsLooper();

private:
	HWND hWnd;
	HINSTANCE hInst;                                // current instance
	WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
	HACCEL hAccelTable;

	IWindow* m_mainWindow;
	std::function<void()> m_fn;
};