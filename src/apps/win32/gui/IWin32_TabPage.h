#pragma once

#include "misc/framework.h"
#include "IWin32Object.h"
#include "IContainer.h"
#include "IControl.h"

#define ITabPage IWin32_TabPage

class IWin32_TabPage : public IControl, public IWin32Object, public IContainer {
public:
	static INT_PTR CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	IWin32_TabPage(HWND parent, DWORD resourceId);
	virtual ~IWin32_TabPage();

public:
	void show();
	void hide();

protected:
	virtual void onCreateTabPage() = 0;

private:
	void injectLongPtr();
	bool shouldInjectLongPtr();
};