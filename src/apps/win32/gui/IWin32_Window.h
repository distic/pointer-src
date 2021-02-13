#pragma once

#include "misc/framework.h"
#include "IWin32Object.h"
#include "IContainer.h"
#include "IResizableControl.h"
#include "IWin32_NotifyIcon.h"
#include <vector>

#define IWindow IWin32_Window

class IWin32_Window : public IWin32Object, public IContainer, IResizableControl {
public:
	/* Used for normal windows */
	static INT_PTR CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	/* Used for Dialogs */
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	IWin32_Window(DWORD resourceId);
	virtual ~IWin32_Window();

protected:
	virtual void onCreateWindow() = 0;
	virtual void onPaint() {
		/* do nothing by default */
	}
	virtual int onCtlColorStatic(WPARAM wParam) {
		/* do nothing by default  */
		return 0;
	}

	virtual void onNotifyIconPrimaryClick() {
		/* do nothing by default */
	}

	virtual void onNotifyIconSecondaryClick() {
		/* do nothing by default */
	}

	virtual void onWindowLostFocus() {
		/* do nothing by default */
	}

public:
	static std::vector<IWindow*> getAllWindows();


public:
	void show();
	void hide();
	void showDialog(HWND hWndParent);
	void close();
	void setTitleBarIcon(DWORD resId);
	void setTitle(const char* title);
	void setNotifyIcon(INotifyIcon* ni);
	bool isVisibe();

	// Inherited via IResizableControl
	virtual void setSize(int width, int height) override;
	virtual void setLocation(int x, int y) override;

protected:
	WCHAR szTitle[MAX_LOADSTRING]; // The title bar text
	INotifyIcon* m_notifyIcon;
};