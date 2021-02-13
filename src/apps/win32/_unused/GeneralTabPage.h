#pragma once

#include "arch/arch_gui/IWin32_TabPage.h"
#include "arch/arch_gui/IWin32_Label.h"
#include "arch/arch_gui/IWin32_Button.h"
// #include "PowtipsProxy.h"
// #include "Powtipd.h"

class GeneralTabPage : public ITabPage {
public:
	GeneralTabPage(HWND tab);
	virtual ~GeneralTabPage();

	void serviceToggleButton_Clicked();

protected:
	// Inherited via IWin32_TabPage
	virtual void onCreateTabPage() override;

private:
	void doStartService();
	void doStopService();

	bool isPowtipsRunning() const;

public:
	ILabel* m_serviceStatusLabel;
	ILabel* m_serviceLastRunLabel;
	IButton* m_serviceToggleButton;

	// PowtipsProxy& m_powtipsProxy;
	// Powtipd& m_powtipd;
};