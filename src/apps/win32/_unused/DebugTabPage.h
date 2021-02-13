#pragma once

#include "arch/arch_gui/IWin32_TabPage.h"
#include "arch/arch_gui/IWin32_Button.h"

class DebugTabPage : public ITabPage {
public:
	DebugTabPage(HWND tab);
	virtual ~DebugTabPage();

	void taskManagerButton_Clicked();

	// Inherited via ITabPage
	virtual void onCreateTabPage() override;

private:
	IButton* m_taskManagerButton;
};