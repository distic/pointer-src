#pragma once

#include "IWin32_TabPage.h"
#include "IWin32_Window.h"
#include "IWin32Object.h"
#include "IControl.h"

#define ITabControl IWin32_TabControl

class IWin32_TabControl : public IControl, public IWin32Object {
public:
	IWin32_TabControl(IWindow&, DWORD resourceId);
	virtual ~IWin32_TabControl();

	void addTabPage(const char* title, ITabPage*);

	void setDefaultTabIndex(int index);

private:
	void invalidatePlacementParams();
	void onTabSelectionChanged();
	void doHideAll();

private:
	TCITEM m_tci = { 0 };
	RECT rc;
	POINT offset = { 0 };

	int m_defaultIndex;
	std::vector<ITabPage*> m_tabPages;
};