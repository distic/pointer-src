#include "IWin32_WinMain.h"
#include <assert.h>
#include "IWin32_ExceptionDialogBox.h"

#include "../gui/win32/misc/resource.h" // HACK: shouldn't supposed to be here!!

#pragma comment(lib,"comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

IWin32_WinMain::IWin32_WinMain(IWindow& w) :
	m_mainWindow(&w)
{

}

IWin32_WinMain::~IWin32_WinMain()
{
	// do nothing.
}

ATOM
IWin32_WinMain::myRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	//wcex.lpfnWndProc = MainWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

void 
IWin32_WinMain::registerExtraLoopFunction(std::function<void()> fn)
{
	m_fn = fn;
}

BOOL
IWin32_WinMain::initInstance(HINSTANCE hInstance, int nCmdShow)
{
	m_mainWindow->showDialog(NULL);

	hInst = hInstance; // Store instance handle in our global variable

	return TRUE;
}

int
IWin32_WinMain::runWindowsLooper()
{
	__try {
		return doRunWindowsLooper();
	}
	__except (IWin32_ExceptionDialogBox::showDialog(GetExceptionInformation()))
	{
		IWin32_ExceptionDialogBox::finishCatch();
	}

	return 0;
}

int
IWin32_WinMain::doRunWindowsLooper()
{
	HINSTANCE hInstance = GetModuleHandle(0);
	INT nCmdShow = SW_SHOW;

	// Initialize global strings
	LoadStringW(hInstance, IDC_PROJECT1, szWindowClass, MAX_LOADSTRING);
	myRegisterClass(hInstance);

	// Perform application initialization:
	if (!initInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT1));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
			m_fn();
		}
	}

	return (int)msg.wParam;
}

IWindow* 
IWin32_WinMain::getMainWindow() const
{
	assert(m_mainWindow != nullptr);
	return m_mainWindow;
}